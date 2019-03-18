#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "structures.h"
#include "tcp.h"

char recv_port[50];
uint32_t range, num_nodes;

void init_logger(int *listen_sock, char **args) {
  char *ptr;
  strcpy(recv_port, args[1]);

  range = strtol(args[2], &ptr, 10);
  num_nodes = strtol(args[3], &ptr, 10);

  start_listen(listen_sock, recv_port);
}

// Populates a node from recieved packet.
void unpack_ntol_data(Node *node, char *buffer) {
  uint32_t id, x, y;
  char recv_port[50];

  id = 0;
  x = 0;
  y = 0;

  // Extract the ID from the message.
  for(int i = 0; i < sizeof(uint32_t); i++) {
    id += buffer[i] << (i * 8);
  }

  // Extract the recieve port from the message.
  memmove(node->recv_port, &buffer[sizeof(uint32_t)], 50);

  // Extract the x-coordinate from the message.
  for(int i = 0; i < sizeof(uint32_t); i++) {
    x += buffer[i + sizeof(uint32_t) + 50] << (i * 8);
  }

  // Extract the y-coordinate from the message.
  for(int i = 0; i < sizeof(uint32_t); i++) {
    y += buffer[i + sizeof(uint32_t) * 2 + 50] << (i * 8);
  }

  node->id = ntohl(id);
  node->x = ntohl(x);
  node->y = ntohl(y);
}

int main(int argc, char *argv[]) {
  int listen_sock, main_sock;
  char s[100];
  struct sockaddr_storage node_addr;
  socklen_t node_addrlen;

  init_logger(&listen_sock, argv);

  while(1) { // main accept() loop
    node_addrlen = sizeof(node_addr);
    main_sock = accept(listen_sock, (struct sockaddr *) &node_addr, &node_addrlen);

    if (main_sock == -1) {
      perror("accept");
      continue;
    }

    if (fork() == 0) { 
      close(listen_sock); // child doesn't need the listener
      char msg[100];
      recv_all(main_sock, msg, 100);

      Node *node;
      node = malloc(sizeof(*node));

      unpack_ntol_data(node, msg);
      printf("Node: %d Port: %s Location: (%d, %d)\n", node->id, node->recv_port, node->x, node->y);
      
      close(main_sock);
      exit(0);
    }
    
    close(main_sock); // parent doesn't need this
  }

  return 0;
}

// Have a buffer for node struct objects. The number of nodes
// input on the command line will be the size of that buffer.

// Node node_buffer[command_line_arg];

// Have a function which converts the incoming packet into a node object
// if recieving data packet from node. Once the above buffer is filled 
// stop timer and print out runtime. (Enjoy!)