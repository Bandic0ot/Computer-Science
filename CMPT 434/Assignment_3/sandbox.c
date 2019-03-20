#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>

#include "structures.h"

#define NOT_IN_RANGE "NIR"
#define IN_RANGE "IR"
#define NODE_REQUEST "NR"
#define NO_MORE_NODE "NMN"
#define BASESTATION 500

Node *init_node(char **args) {
  Node *node;
  char *ptr;

  node = malloc(sizeof(*node));
  
  memset(node->node_buffer, 0, sizeof(*node));

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

// char *create_packet(Node *node) {
//   uint32_t id, packet_length; 
//   char *packet;
  
//   id = htonl(node->id);
//   packet_length = htonl(sizeof(uint32_t) + sizeof(node->id) + sizeof(node->data));

//   packet = malloc(sizeof(uint32_t) + sizeof(node->id) + sizeof(node->data));

//   memmove(packet, &packet_length, sizeof(uint32_t)); // Add the length
//   memmove(&packet[sizeof(u_int32_t)], &id, sizeof(node->id)); // Add the ID
//   memmove(&packet[sizeof(u_int32_t) + sizeof(node->id)], node->data, sizeof(node->data)); // Add the data

//   return packet;
// }

// Creates a packet by packing the length of the data into the front of the packet.
char *create_packet(char *data, uint32_t size) {
  uint32_t length;
  char *packet;

  length = htonl(sizeof(uint32_t) + size);

  packet = malloc(sizeof(uint32_t) + size);

  memmove(packet, &length, sizeof(uint32_t));
  memmove(&packet[sizeof(uint32_t)], data, size);

  return packet;
}

// void parse_packet(char *packet) {
//   uint32_t length = 0;
//   uint32_t id = 0;

//   char msg[10];

//   for(int i = 0; i < 4; i++) {
//     length += packet[i] << (i * 8); 
//   }

//   for(int i = 4; i < 8; i++) {
//     id += packet[i] << (i * 8); 
//   }

//   for(int i = 8; i < 18; i++) {
//     msg[i - 8] = packet[i];
//   }
// }

uint32_t parse_packet(char *packet, char *buffer) {
  uint32_t length;

  length = 0;

  for(int i = 0; i < sizeof(uint32_t); i++) {
    length += packet[i] << (i * 8);
  }

  length = ntohl(length);

  memmove(buffer, &packet[sizeof(uint32_t)], length - sizeof(u_int32_t));

  return length;
}

// Appends the second byte array to the first.
char *append_byte_array(char *byte1, char *byte2, uint32_t size1, uint32_t size2) {
  char *byte_array;

  byte_array = malloc(size1 + size2);

  memmove(byte_array, byte1, size1);
  memmove(&byte_array[size1], byte2, size2);

  return byte_array;
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

int unpack_packet_size(char *packet) {
  uint32_t packet_size;

  packet_size = 0;

  for(int i = 0; i < sizeof(uint32_t); i++) {
    packet_size += packet[i] << (i * 8);
  }

  packet_size = ntohl(packet_size);

  return packet_size;
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

void *process_thread() {
  printf("Hello.\n");
}

int main(int argc, char *argv[]) {
  pthread_t pid;
  
  pthread_create(&pid, NULL, process_thread, NULL);

  printf("World.\n");
  pthread_join(pid, NULL);
  

  return EXIT_SUCCESS;
}