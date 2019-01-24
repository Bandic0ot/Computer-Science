#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void create_connection(char *address, char *port, int *sock) {
  int addrinfo_status;
  struct addrinfo hints, *results;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  addrinfo_status = getaddrinfo(address, port, &hints, &results);
  if(addrinfo_status != 0) {
    fprintf(stderr, "%s\n", gai_strerror(addrinfo_status));
    exit(-1);
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
      exit(-1);
    }

    if(r == NULL) {
      fprintf(stderr, "Failed to connect.\n");
      exit(-1);
    }
  }

  return;
}

int file_exists(char *file) {
  if(access(file, F_OK) == 0) {
    printf("The file %s, already exists.", file);
    return 0;
  }

  return -1;
}

// Returns 0 if true, -1 otherwise.
int check_filetype(char *file1, char* file2) {
  char *ext1 = strrchr(file1, '.');
  char *ext2 = strrchr(file2, '.');
  char *pre1 = malloc(sizeof(file1));
  char *pre2 = malloc(sizeof(file2));

  memcpy(pre1, file1, strlen(file1) - strlen(ext1));
  memcpy(pre2, file2, strlen(file2) - strlen(ext2));

  // Check to see if either file is an empty string followed by a "."
  if(strlen(pre1) != 0 && strlen(pre2) != 0) {
    // Make sure each file has the correct extension.
    if(ext1 != NULL && ext2 != NULL) {
      if(strcmp(ext1, ".txt") == 0 && strcmp(ext2, ".txt") == 0) {
        return 0;
      }
    }
  }

  printf("Invalid file type, both files must be of type .txt\n");
  return -1; 
}

void get(char *local_file, char *remote_file, int sock) {
  if(file_exists(local_file) == 0) {
    return;
  }

  char cmd[100] = "GET ";
  char rsp[100];
  int bytes;
  char *msg = strcat(cmd, remote_file);
  
  send(sock, msg, strlen(msg), 0);
  bytes = recv(sock, rsp, sizeof(rsp), 0);
  // rsp[bytes] = '\0';

  printf("%s", rsp);
}

void put(char *local_file, char *remote_file, int sock) {
  if(file_exists(local_file) == 0) {
    return;
  }

  char *cmd = "PUT ";
  char *msg = strcat(cmd, remote_file);
  
  send(sock, msg, strlen(msg), 0);
}

// Takes the given input and separates it by spaces, 
// each word becomes an element of the provided array.
void parse_input(char *input, int sock) {
    char *token;
    char *input_args[50];
    int arg_count = 0;

    // Because fgets reads in a newline when no input is given, we
    // set input_args to NULL in order to avoid a segfault with strtok.
    if(strcmp(input, "\n") != 0) {
      token = strtok(input, " ");
      input_args[arg_count] = token;

      while(token != NULL) {
        arg_count++;
        token = strtok(NULL, " ");
        input_args[arg_count] = token;
      }
    } else {
      input_args[0] = NULL;
    }

    // Strip the arguments of any newline characters.
    if(input_args != NULL) {
      for(int i = 0; i < arg_count; i++) {
        input_args[i] = strtok(input_args[i], "\n");
      }
    }

    if(arg_count == 1) {
      if(strcmp(input_args[0], "quit") == 0) {
        exit(EXIT_SUCCESS);
      }
    } else if(arg_count == 3) {
      if(strcmp(input_args[0], "get") == 0) {
        if(check_filetype(input_args[1], input_args[2]) == 0) {
          get(input_args[1], input_args[2], sock);
        } 
        return;
      } else if(strcmp(input_args[0], "put") == 0) {
        if(check_filetype(input_args[1], input_args[2]) == 0) {
          put(input_args[1], input_args[2], sock);
        } 
        return;
      }
    }
    
    // If the input arguments aren't valid the default behaviour is 
    // to reset the input to NULL and return an invalid message.
    input = NULL;

    printf("Invalid command.\n");
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
  int BUFFER = 100;
  int sock;

  parse_args(argc, argv);
  create_connection(argv[1], argv[2], &sock);

  // Program loop
  while(1) {
    char *input = malloc(sizeof(char) * BUFFER);

    printf("Please enter a command [get|put|quit] [local] [remote]:\n");
    fgets(input, BUFFER, stdin);

    parse_input(input, sock);
  }

  return 0;
}