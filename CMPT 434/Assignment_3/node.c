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

#include "structures.h"
#include "tcp.h"

#define NOT_IN_RANGE "NIR"
#define IN_RANGE "IR"
#define NODE_REQUEST "NR"
#define NO_MORE_NODE "NMN"
#define BASESTATION 500

Node *init_node(char **args) {
  Node *node;
  char *ptr;

  node = malloc(sizeof(*node));
  
  memset(node->node_buffer, 0, sizeof(Node *) * 5);

  node->id = strtol(args[1], &ptr, 10);
  node->distance = strtol(args[3], &ptr, 10);
  node->x = rand() % (1000 + 1 - 0) + 0;
  node->y = rand() % (1000 + 1 - 0) + 0;

  strcpy(node->data, args[2]);
  strcpy(node->ip, "127.0.0.1");
  strcpy(node->recv_port, args[4]);
  strcpy(node->log_hostname, args[5]);
  strcpy(node->log_port, args[6]);

  return node;
}

uint32_t sign() {
  uint32_t sign;

  if(rand() % 2 == 0) {
    sign = 1;
  } else {
    sign = -1;
  }

  return sign;
}

void move(Node *node, uint32_t distance) {
  uint32_t delta_x, delta_y;

  delta_x = sign() * (rand() % (distance + 1 - 0) + 0);
  delta_y = sign() * (distance - abs(delta_x));

  //printf ("Delta: %f, %f\n", delta_x, delta_y);
  
  // Check to see if node exceeds boundaries, if it does "bounce" back.
  if(node->x + delta_x > 1000) {
    uint32_t diff;
    diff = (1000 - node->x);
    node->x += diff - (delta_x - diff);
  } else if(node->x + delta_x < 0) {
    node->x += (abs(delta_x) - node->x) - node->x;
  } else {
    node->x += delta_x;
  }

  if(node->y + delta_y > 1000) {
    uint32_t diff;
    diff = (1000 - node->y);
    node->y += diff - (delta_y - diff);
  } else if(node->y + delta_y < 0) {
    node->y += (abs(delta_y) - node->y) - node->y;
  } else {
    node->y += delta_y;
  }
}

// Creates a node to logger data array.
char *node_to_log_data(uint32_t id, char *recv_port, uint32_t x, uint32_t y) {
  char *data;
  uint32_t packed_id, packed_x, packed_y;

  data = malloc(sizeof(uint32_t) * 3 + 50);
  packed_id = htonl(id);
  packed_x = htonl(x);
  packed_y = htonl(y);

  memmove(data, &packed_id, sizeof(uint32_t));
  memmove(&data[sizeof(uint32_t)], recv_port, 50);
  memmove(&data[sizeof(uint32_t) + 50], &packed_x, sizeof(uint32_t));
  memmove(&data[sizeof(uint32_t) * 2 + 50], &packed_y, sizeof(uint32_t));

  return data;
}

// Populates a node from recieved n2n packet.
void unpack_node_connect_data(Node *node, char *buffer) {
  uint32_t id;

  id = 0;

  // Extract the ID from the message.
  for(int i = 0; i < sizeof(uint32_t); i++) {
    id += buffer[i] << (i * 8);
  }

  node->id = ntohl(id);

  // Extract the ip from the message.
  memmove(node->ip, &buffer[sizeof(uint32_t)], 50);

  // Extract the recieve port from the message.
  memmove(node->recv_port, &buffer[sizeof(uint32_t) + 50], 50);
}

// Checks to see if the first location is closer than the second location.
int closer(int x1, int y1, int x2, int y2) {
  int manhattan1, manhattan2;

  manhattan1 = abs(BASESTATION - x1) + abs(BASESTATION - y1);
  manhattan2 = abs(BASESTATION - x2) + abs(BASESTATION - y2);

  if(manhattan1 < manhattan2) {
    return 0;
  } else {
    return -1;
  }
}

void transmit(Node *node) {
  int main_sock;
  char *packet;
  char buffer[100];

  packet = node_to_log_data(node->id, node->recv_port, node->x, node->y);

  create_connection(node->log_hostname, node->log_port, &main_sock);
  
  send_all(main_sock, packet, 62);
  recv_all(main_sock, buffer, sizeof(buffer));
  
  if(strcmp(buffer, IN_RANGE) == 0) {
    send_all(main_sock, node->data, sizeof(node->data));
  } else {
    recv_all(main_sock, buffer, sizeof(buffer));

    while(strcmp(buffer, NO_MORE_NODE) != 0) {
      Node *connect_node;
      int node_sock;

      connect_node = malloc(sizeof(*connect_node));
      unpack_node_connect_data(connect_node, buffer);

      //create_connection(connect_node->ip, connect_node->recv_port, &node_sock);
      recv_all(main_sock, buffer, sizeof(buffer));
    }

    printf("No more nodes.\n");
  }

  close(main_sock);
}

int main(int argc, char *argv[]) {
  Node *my_node;
  int listen_sock;

  srand(time(NULL));
  
  if(argc != 7) {
    printf("Incorrect number of arguments.\n");

    exit(EXIT_FAILURE);
  }

  my_node = init_node(argv);
  start_listen(&listen_sock, my_node->recv_port);

  while(1) {
    transmit(my_node);
    move(my_node, my_node->distance);
    printf("(%d, %d)\n", my_node->x, my_node->y);
    sleep(1);
  }

  return 0;
}