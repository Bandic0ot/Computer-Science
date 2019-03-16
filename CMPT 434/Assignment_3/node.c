#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "structures.h"
#include "tcp.h"

Node *init_node(char **args) {
  Node *node;
  char *ptr;

  node = malloc(sizeof(*node));
  node->buffer = malloc(sizeof(Node) * 10);

  node->id = strtol(args[1], &ptr, 10);
  node->distance = strtol(args[3], &ptr, 10);
  node->x = ((float) rand() / (float) RAND_MAX) * (1000 - 0) + 0;
  node->y = ((float) rand() / (float) RAND_MAX) * (1000 - 0) + 0;

  strcpy(node->data, args[2]);
  strcpy(node->recv_port, args[4]);
  strcpy(node->log_hostname, args[5]);
  strcpy(node->log_port, args[6]);

  return node;
}

float sign() {
  float sign;
  sign = ((float) rand() / (float) RAND_MAX) * (1 - (-1)) + (-1);

  if(sign > 0) {
    sign = 1;
  } else {
    sign = -1;
  }

  return sign;
}

void move(Node *node, float distance) {
  float delta_x, delta_y;

  delta_x = sign() * ((float) rand() / (float) (RAND_MAX / distance));
  delta_y = sign() * ((float) distance - fabs(delta_x));

  //printf ("Delta: %f, %f\n", delta_x, delta_y);
  
  // Check to see if node exceeds boundaries, if it does "bounce" back.
  if(node->x + delta_x > 1000) {
    float diff;
    diff = (1000 - node->x);
    node->x += diff - (delta_x - diff);
  } else if(node->x + delta_x < 0) {
    node->x += (fabs(delta_x) - node->x) - node->x;
  } else {
    node->x += delta_x;
  }

  if(node->y + delta_y > 1000) {
    float diff;
    diff = (1000 - node->y);
    node->y += diff - (delta_y - diff);
  } else if(node->y + delta_y < 0) {
    node->y += (fabs(delta_y) - node->y) - node->y;
  } else {
    node->y += delta_y;
  }
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

  create_connection(node->log_hostname, node->log_port, &main_sock);
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
    move(my_node, (float) my_node->distance);
    printf("(%f, %f)\n", my_node->x, my_node->y);
    sleep(1);
  }

  return 0;
}