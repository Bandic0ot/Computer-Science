#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "30081"
#define BUFFER_SIZE 1000000

int file_exists(char *file) {
  if(access(file, F_OK) == 0) {
    return 0;
  }

  return -1;
}

// Retrieve the file requested in the message.
void get(char *file, int sock) {
  FILE *f;
  size_t text_size;
  char *msg;
  char buffer[BUFFER_SIZE + 1];

  if(file_exists(file) != 0) {
    msg = "File does not exist.\n";
    send(sock, msg, strlen(msg), 0);
    return;
  }

  f = fopen(file, "r");

  if(f != NULL) {
    text_size = fread(buffer, sizeof(char), BUFFER_SIZE, f);

    if(ferror(f) != 0) {
      printf("Error reading file.");
      exit(EXIT_FAILURE);
    } 

    buffer[text_size] = '\0';
  }

  fclose(f);

  int bytes_remaining = text_size + 1;
  int bytes_sent = 0;
  int bytes;

  while(bytes_sent < text_size + 1) {
    bytes = send(sock, &buffer[bytes_sent], bytes_remaining, 0);
    bytes_sent += bytes;
    bytes_remaining -= bytes;

    if(bytes == -1) {
      perror("Send");
      exit(EXIT_FAILURE);
    }
  }
}

// Write to the file specified in the message.
void put(char *file, int sock) {
  FILE *f;
  char buffer[BUFFER_SIZE + 1];
  int bytes = 0;
  int bytes_recv = 0;

  if(file_exists(file) == 0) {
    return;
  }

  // Loop the recv until we see a nul terminator.
  do {
    bytes = recv(sock, &buffer[bytes_recv], BUFFER_SIZE + 1, 0);
    bytes_recv += bytes;

    if(bytes == -1) {
      perror("recv");
      exit(EXIT_FAILURE);
    } else if (bytes == 0) {
      break;
    }
  } while(buffer[bytes_recv - 1] != '\0');

  f = fopen(file, "w");

  if(f != NULL) {
    fwrite(buffer, sizeof(char), bytes_recv - 1, f);
    
    if(ferror(f) != 0) {
      printf("Error writing to file.");
      exit(EXIT_FAILURE);
    } 
  }

  fclose(f);
}

// Taken from Beej's Networking guide
void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *) sa)->sin_addr);
  }
  
  return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

// Main server function
void start_server(int *listen_sock) {
  struct addrinfo hints, *results;
  int addrinfo_status;
  char *address = malloc(sizeof(socklen_t));

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  addrinfo_status = getaddrinfo(NULL, PORT, &hints, &results);

  if(addrinfo_status != 0) {
    fprintf(stderr, "%s", gai_strerror(addrinfo_status));
    return;
  }

  for(struct addrinfo *r = results; r != NULL; r = r->ai_next) {
    // Create a socket for listening.
    *listen_sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol);

    if(*listen_sock == -1) {
      perror("Socket");
      exit(EXIT_FAILURE);
    }

    // Bind to the designated port.
    if(bind(*listen_sock, r->ai_addr, r->ai_addrlen) == -1) {
      perror("Bind");
      exit(EXIT_FAILURE);
    }

    if(r->ai_family == AF_INET) {
      inet_ntop(r->ai_family, &(((struct sockaddr_in *) r->ai_addr)->sin_addr), address, sizeof(address));
    } else {
      inet_ntop(r->ai_family, &(((struct sockaddr_in6 *) r->ai_addr)->sin6_addr), address, sizeof(address));
    }

    break;
  }

  freeaddrinfo(results);

  if(listen(*listen_sock, 10) == -1) {
    perror("Listen");
    exit(EXIT_FAILURE);
  }

  printf("Server started on %s, port %s...\n", address, PORT);
}

int main(int argc, char *argv[]) {
  int listen_sock, main_sock, bytes;
  struct sockaddr_storage client_addr;
  socklen_t client_addrlen;
  char s[100];
  char msg[100];

  start_server(&listen_sock);

  client_addrlen = sizeof(socklen_t);
  main_sock = accept(listen_sock, (struct sockaddr *) &client_addr, &client_addrlen);

  if(main_sock == -1) {
    perror("Accept");
    exit(EXIT_FAILURE);
  }

  inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *) &client_addr), s, sizeof(s));
  printf("Got connection from %s\n", s);

  bytes = recv(main_sock, msg, sizeof(msg), 0); 

  if(bytes == -1) {
    perror("Recieve");
    exit(EXIT_FAILURE);
  } else if(bytes == 0) {
    printf("Connection closed.\n");
    close(main_sock);
    exit(EXIT_FAILURE);
  }

  msg[bytes] = '\0';

  char *command, *file;

  command = strtok(msg, " ");
  file = strtok(NULL, " ");

  if(strcmp(command, "GET") == 0) {
    get(file, main_sock);
  } else {
    put(file, main_sock);
  }

  close(main_sock);

  return 0;
}
