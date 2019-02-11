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

#include "udp.h"
#include "queue.h"

#define REQUIRED_NUM_ARGS 5
#define MAX_DATA_SIZE 100

// Initializes a socket for UDP communication.
// Pre: A valid IPv4 or IPv6 address and a valid port number.
// Post: sock is initialized with a socket descriptor.
struct addrinfo *init_socket(int *sock, char *address, char *port) {
  int addrinfo_status;
  struct addrinfo hints, *results, *info;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  addrinfo_status = getaddrinfo(address, port, &hints, &results);
  if(addrinfo_status != 0) {
    fprintf(stderr, "%s\n", gai_strerror(addrinfo_status));
    exit(EXIT_FAILURE);
  }

  for(struct addrinfo *r = results; r != NULL; r = r->ai_next) {
    *sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol);

    if(*sock == -1) {
      perror("Socket");
      exit(EXIT_FAILURE);
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

    info = r;
  }

  return info;
}

// Parse the input and ensure that all the input is valid.
// Pre: Null values for all input, except argc and argv.
// Post: All values are set.
void parse_args(char **args, int count, char *address, char *port, int *win_size, int *timeout) {
  char *ptr;

  if(count != REQUIRED_NUM_ARGS) {
    printf("Invalid number of arguments.\n");
    exit(EXIT_FAILURE);
  }

  strcpy(address, args[1]);
  strcpy(port, args[2]);

  *win_size = strtol(args[3], &ptr, 10);

  if(*win_size == 0) {
    printf("Sending window size must be valid positive non-zero integer.\n");
    exit(EXIT_FAILURE);
  }

  *timeout = strtol(args[4], &ptr, 10);

  if(*timeout == 0) {
    printf("Timeout must be valid positive non-zero integer.\n");
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char *argv[]) {
  struct addrinfo *info;
  int server_sock, win_size, timeout, seq_num;
  char *address, *port, **window;

  window = malloc(sizeof(char *) * win_size);
  address = malloc(sizeof(uint32_t));
  port = malloc(sizeof(uint32_t));

  parse_args(argv, argc, address, port, &win_size, &timeout);
  info = init_socket(&server_sock, address, port);

  initialize(win_size);
  seq_num = 1;

  while(1) {
    char *msg, *frame; // sizeof(uint32_t) * 3 to account for control bytes
    int next_seq_num, msg_length;
    size_t msg_size;

    frame = malloc(MAX_DATA_SIZE + sizeof(u_int32_t) * 3);
    msg = malloc(MAX_DATA_SIZE);
    msg_size = MAX_DATA_SIZE;
    next_seq_num = seq_num + 1;

    printf("Please enter a message to send.\n");
    getline(&msg, &msg_size, stdin);

    msg_length = strlen(msg);

    if(full() == 0) {
      printf("The sending window is full. \n");
      continue;
    }

    serialize_frame(&seq_num, &next_seq_num, msg, &msg_length, frame);
    enqueue(window, frame);
    send_frame(server_sock, frame);

    seq_num++;
  }

  return 0;
}