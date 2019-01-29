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

void pack_length(char *msg, int msg_length, char *buffer) {
  uint32_t length = htonl(msg_length);

  memcpy(buffer, &length, sizeof(uint32_t));
  memcpy(&buffer[sizeof(uint32_t)], msg, msg_length);
}

int unpack_length(char *msg) {
  uint32_t msg_length;

  msg_length = ntohl(msg[0] + (msg[1] << 8) + (msg[2] << 16) + (msg[3] << 24));

  return msg_length;
}

void send_all(int sock, char *msg, int msg_length) {
  int bytes, bytes_sent, bytes_remaining;
  char buffer[msg_length + sizeof(uint32_t)];

  pack_length(msg, msg_length, buffer);

  bytes_remaining = msg_length + sizeof(uint32_t);
  bytes_sent = 0;

  while(bytes_sent < msg_length + sizeof(uint32_t)) {
    bytes = send(sock, &buffer[bytes_sent], bytes_remaining, 0);
    bytes_sent += bytes;
    bytes_remaining -= bytes;

    if(bytes == -1) {
      perror("Send");
      exit(EXIT_FAILURE);
    }
  }
}

int recv_all(int sock, char *buffer, int buffer_length) {
  int bytes, bytes_recv, msg_length;
  char length_buffer[sizeof(uint32_t)];

  recv(sock, length_buffer, sizeof(u_int32_t), 0);

  msg_length = unpack_length(length_buffer);

  bytes_recv = 0;

  while(bytes_recv < msg_length) {
    bytes = recv(sock, &buffer[bytes_recv], buffer_length, 0);
    bytes_recv += bytes;

    if(bytes == -1) {
      perror("Recv");
      printf("File may be too large for buffer.\n");
      exit(EXIT_FAILURE);
    } else if (bytes == 0) {
      printf("Connection closed.\n");
      exit(EXIT_FAILURE);
    }
  
  }

  buffer[bytes_recv] = '\0';

  return bytes_recv - 1;
}

// Taken from Beej's Networking guide
void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *) sa)->sin_addr);
  }
  
  return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}