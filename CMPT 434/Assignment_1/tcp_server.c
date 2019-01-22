#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT "30080"

int file_exists(char *file) {
  if(access(file, F_OK) == 0) {
    return 0;
  }

  return -1;
}

// Returns 0 if true, -1 otherwise.
int check_filetype(char *file1, char* file2) {
  char *ext1 = strrchr(file1, '.');
  char *ext2 = strrchr(file2, '.');

  if(ext1 != NULL && ext2 != NULL) {
    if(strcmp(ext1, ".txt") == 0 && strcmp(ext2, ".txt") == 0) {
      return 0;
    }
  }

  printf("Invalid file type, both files must be of type .txt\n");
  return -1; 
}

void get(char *local_file, char *remote_file) {
  if(file_exists(local_file) == 0) {
    printf("The file %s, already exists.", local_file);
    return;
  }
  printf("GET: %s %s\n", local_file, remote_file);
}

void put(char *local_file, char *remote_file) {
  printf("PUT: %s %s\n", local_file, remote_file);
}

void start_server(int *listen_sock, int *main_sock) {
  struct addrinfo hints, *results;
  int addrinfo_status;

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
      continue;
    }

    // Bind to the designated port.
    if(bind(*listen_sock, r->ai_addr, r->ai_addrlen) == -1) {
      perror("Bind");
      continue;
    }

    break;
  }

  freeaddrinfo(results);

  if(listen(*listen_sock, 10) == -1) {
    perror("Listen");
    return;
  }

  printf("Server started...\n");
}

int main(int argc, char *argv[]) {
  int listen_sock, main_sock;

  start_server(&listen_sock, &main_sock);

  return 0;
}