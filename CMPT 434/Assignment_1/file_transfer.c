#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "file_transfer.h"

#define BUFFER_SIZE 1000000

int file_exists(char *file) {
  if(access(file, F_OK) == 0) {
    return 0;
  }

  return -1;
}

void buffer_to_file(char *file, char *buffer, int bytes_recv) {
  FILE *f;
  size_t file_bytes;

  f = fopen(file, "w");

  if(f != NULL) {
    file_bytes = fwrite(buffer, sizeof(char), bytes_recv, f);

    if(ferror(f) != 0) {
      printf("Error writing buffer to file.");
      exit(EXIT_FAILURE);
    }

    fclose(f);
  }
}

int file_to_buffer(char *file, char *buffer) {
  FILE *f;
  size_t file_bytes;

  f = fopen(file, "r");

  if(f != NULL) {
    file_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, f);
    
    if(ferror(f) != 0) {
      printf("Error reading file to buffer.");
      exit(EXIT_FAILURE);
    }

    buffer[file_bytes] = '\0';

    fclose(f);
  }

  return file_bytes + 1;
}

void send_all(int sock, char *msg, int msg_length) {
  int bytes, bytes_sent, bytes_remaining;

  bytes_remaining = msg_length;
  bytes_sent = 0;

  while(bytes_sent < msg_length) {
    bytes = send(sock, &msg[bytes_sent], bytes_remaining, 0);
    bytes_sent += bytes;
    bytes_remaining -= bytes;

    if(bytes == -1) {
      perror("Send");
      exit(EXIT_FAILURE);
    }
  }
}

int recv_all(int sock, char *buffer, int buffer_length) {
  int bytes, bytes_recv;

  bytes_recv = 0;

  do {
    bytes = recv(sock, &buffer[bytes_recv], buffer_length, 0);
    bytes_recv += bytes;

    if(bytes == -1) {
      perror("recv");
      exit(EXIT_FAILURE);
    } else if (bytes == 0) {
      printf("Connection closed.\n");
      exit(EXIT_FAILURE);
    }
  
  } while(buffer[bytes_recv - 1] != '\0');

  return bytes_recv - 1;
}