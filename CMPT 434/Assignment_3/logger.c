/* Matthew Mulenga
 * mam558
 * 11144528
 */

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
#include <sys/wait.h>

#include "structures.h"
#include "tcp.h"

#define NOT_IN_RANGE "NIR"
#define IN_RANGE "IR"
#define NODE_REQUEST "NR"
#define NO_MORE_NODE "NMN"
#define BASESTATION 500

char recv_port[50];
uint32_t range, num_nodes;

void init_logger(int *listen_sock, char **args) {
  char *ptr;
  strcpy(recv_port, args[1]);

  range = strtol(args[2], &ptr, 10);
  num_nodes = strtol(args[3], &ptr, 10);

  start_listen(listen_sock, recv_port);
}

// Populates a node from recieved n2l packet.
void unpack_node_to_log_data(Node *node, char *buffer) {
  uint32_t id, x, y;

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

// Creates a node to node data array.
char *node_connect_data(uint32_t id, char *ip, char *recv_port) {
  char *data;
  uint32_t packed_id;

  data = malloc(sizeof(uint32_t) + 50 * 2); // 50 is the size of the ip and recv_port arrays
  packed_id = htonl(id);

  memmove(data, &packed_id, sizeof(uint32_t));
  memmove(&data[sizeof(uint32_t)], ip, 50);
  memmove(&data[sizeof(uint32_t) + 50], recv_port, 50);

  return data;
}

char *in_range(int x1, int y1, int x2, int y2, int t) {
  if((x1 < x2 + t && x1 > x2 - t) && (y1 < y2 + t && y1 > y2 - t)) {
    return IN_RANGE;
  } else {
    return NOT_IN_RANGE;
  }
}

int main(int argc, char *argv[]) {
  Node **node_array;
  time_t start, end;
  int listen_sock, main_sock, t_range, num_nodes, node_counter, transmission_counter;
  char *ptr;
  struct sockaddr_storage node_addr;
  socklen_t node_addrlen;

  time(&start);

  init_logger(&listen_sock, argv);

  t_range = strtol(argv[2], &ptr, 10);
  num_nodes = strtol(argv[3], &ptr, 10);
  node_array = malloc(sizeof(Node *) * num_nodes);
  node_counter = 0;
  transmission_counter = 0;

  memset(node_array, 0, sizeof(Node *) * num_nodes);

  while(1) { // main accept() loop
    node_addrlen = sizeof(node_addr);
    main_sock = accept(listen_sock, (struct sockaddr *) &node_addr, &node_addrlen);

    if (main_sock == -1) {
      perror("accept");
      continue;
    }

    if (fork() == 0) { 
      close(listen_sock); // child doesn't need the listener
      Node *node;
      char *range_packet;
      char buffer[100];

      node = malloc(sizeof(*node));

      recv_all(main_sock, buffer, 100);
      unpack_node_to_log_data(node, buffer);

      range_packet = in_range(node->x, node->y, BASESTATION, BASESTATION, t_range);

      send_all(main_sock, range_packet, sizeof(range_packet));

      if(strcmp(range_packet, "IR") == 0) {
        recv_all(main_sock, buffer, 100);
        strcpy(node->data, buffer);

        if(node_array[node->id] == NULL) {
          node_array[node->id] = node;
          node_counter++;
        }

        printf("Node %d -> Logger | Data: %s\n", node->id, node->data);
      } else {
        for(int i = 0; i < num_nodes; i++) {
          // Check to see if the node we are preparing to send info on is:
          // A) A valid node. B) Not the same node we are already connected to.
          if(node_array[i] != NULL && node_array[i]->id != node->id) {
            // Check to see if a node is in range to the node currently connected.
            if(in_range(node_array[i]->x, node_array[i]->y, node->x, node->y, t_range) == IN_RANGE) {
              // TODO: Transmit node connection info.
              char *connect_packet;

              connect_packet = node_connect_data(node_array[i]->id, node_array[i]->ip, node_array[i]->recv_port);
              send_all(main_sock, connect_packet, sizeof(connect_packet));
            }
          }
        }

        send_all(main_sock, NO_MORE_NODE, sizeof(NO_MORE_NODE));
      }
      
      close(main_sock);
      exit(node_counter);
    }

    // Please never do this in the industry.
    wait(&node_counter);
    node_counter = node_counter / 255;
    printf("%d\n", node_counter);
    
    if(node_counter == num_nodes) {
      time(&end);

      printf("All packets recieved.\n");
      printf("Elapsed time: %fs\n", (double) (end - start));
      printf("Node to node transmissions: %d\n", transmission_counter);

      close(main_sock);

      break;
    }
  }

  return 0;
}