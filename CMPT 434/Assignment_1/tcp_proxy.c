/* Matthew Mulenga
 * mam558
 * 11144528
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "file_transfer.h"

#define PORT "30081"
#define BUFFER_SIZE 1000000

// Main server function
void start_server(int *listen_sock) {
  struct addrinfo hints, *results, *r;
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

  for(r = results; r != NULL; r = r->ai_next) {
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

  if(r == NULL) {
    fprintf(stderr, "Server failed to bind.\n");
    exit(EXIT_FAILURE);
  }

  freeaddrinfo(results);

  if(listen(*listen_sock, 10) == -1) {
    perror("Listen");
    exit(EXIT_FAILURE);
  }

  printf("Proxy server started on %s, port %s...\n", address, PORT);
}

void create_connection(char *address, char *port, int *sock) {
  int addrinfo_status;
  struct addrinfo hints, *results;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  addrinfo_status = getaddrinfo(address, port, &hints, &results);
  if(addrinfo_status != 0) {
    fprintf(stderr, "%s\n", gai_strerror(addrinfo_status));
    exit(EXIT_FAILURE);
  }

  for(struct addrinfo *r = results; r != NULL; r = r->ai_next) {
    *sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol);

    if(*sock == -1) {
      perror("Socket");
      exit(-1);
    }

    if(connect(*sock, r->ai_addr, r->ai_addrlen) == -1) {
      close(*sock);
      perror("Connect");
      exit(EXIT_FAILURE);
    }

    if(r == NULL) {
      fprintf(stderr, "Failed to connect.\n");
      exit(EXIT_FAILURE);
    }
  }

  return;
}

int duplicate(char *buffer, int size, char *copy) {
  int marker = 0;

  for(int i = 0; i < size; i++) {
    copy[marker] = buffer[i];

    if(buffer[i] == 'c' || buffer[i] == 'm' || buffer[i] == 'p' || buffer[i] == 't') {
      marker++;
      copy[marker] = buffer[i];
    }

    marker++;

    if(marker > BUFFER_SIZE) {
      printf("Modified file too large for buffer.\n");
      exit(EXIT_FAILURE);
    }
  }

  return marker;
}

// Retrieve the file requested in the message.
void get(char *msg, int client_sock, int server_sock) {
  char buffer[BUFFER_SIZE];
  char copy[BUFFER_SIZE];
  int msg_length, copy_length;

  send_all(server_sock, msg, strlen(msg));

  msg_length = recv_all(server_sock, buffer, BUFFER_SIZE);
  copy_length = duplicate(buffer, msg_length, copy);
  
  send_all(client_sock, copy, copy_length);
}

// Write to the file specified in the message.
void put(char *msg, int client_sock, int server_sock) {
  char buffer[BUFFER_SIZE];
  char copy[BUFFER_SIZE];
  int msg_length, copy_length;

  send_all(server_sock, msg, strlen(msg));

  msg_length = recv_all(client_sock, buffer, BUFFER_SIZE);
  copy_length = duplicate(buffer, msg_length, copy);

  send_all(server_sock, copy, copy_length);
}

void parse_args(int count, char **args) {
  if(count == 3) {
    void *dst;
    char *address = args[count - 2];

    // Make sure the first argument is a valid IPv4 or IPv6 address.
    if(inet_pton(AF_INET, address, &dst) == 1) {
      return;
    } else if(inet_pton(AF_INET6, address, &dst) == 1) {
      return;
    }
  }
  
  printf("Invalid command line arguments. Must be a valid IPv4 or IPv6 address.\n");
  exit(-1);
}

int main(int argc, char *argv[]) {
  int server_sock, listen_sock, client_sock;
  struct sockaddr_storage client_addr;
  socklen_t client_addrlen;
  char s[100];
  char cmd_msg[100];

  parse_args(argc, argv);
  create_connection(argv[1], argv[2], &server_sock);
  start_server(&listen_sock);

  client_addrlen = sizeof(socklen_t);
  client_sock = accept(listen_sock, (struct sockaddr *) &client_addr, &client_addrlen);

  if(client_sock == -1) {
    perror("Accept");
    exit(EXIT_FAILURE);
  }

  inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *) &client_addr), s, sizeof(s));
  printf("Got connection from %s\n", s);

  recv_all(client_sock, cmd_msg, 100); 

  char *command, *msg;

  strcpy(msg, cmd_msg);
  command = strtok(cmd_msg, " ");

  if(strcmp(command, "GET") == 0) {
    get(msg, client_sock, server_sock);
  } else {
    put(msg, client_sock, server_sock);
  }

  close(client_sock);

  return 0;
}