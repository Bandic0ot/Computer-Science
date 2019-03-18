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

Node *init_node(char **args) {
  Node *node;
  char *ptr;

  node = malloc(sizeof(*node));
  node->buffer = malloc(sizeof(Node) * 10);

  node->id = strtol(args[1], &ptr, 10);
  node->distance = strtol(args[3], &ptr, 10);
  node->x = rand() % (1000 + 1 - 0) + 0;
  node->y = rand() % (1000 + 1 - 0) + 0;

  strcpy(node->data, args[2]);
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

  delta_x = sign() * (rand() / (RAND_MAX / distance));
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
char *ntol_data(uint32_t id, char *recv_port, uint32_t x, uint32_t y) {
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

/* transmit() {
 * create_connection(logger)
 * send(id, port, location)
 * 
 * if(recv == in_range)
 *    send(data)
 * else
 *    while(recv(node) != no_nodes_left)
 *        create_connection(node)
 *        recv(location)
 *        if(location == closer)
 *            send(data)
 *        else
 *            send(nvm)
 *            close_connection(node)
 * close_connection(logger)
 */

void transmit(Node *node) {
  int main_sock;
  char *packet;

  packet = ntol_data(node->id, node->recv_port, node->x, node->y);

  create_connection(node->log_hostname, node->log_port, &main_sock);
  
  send_all(main_sock, packet, 62);
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