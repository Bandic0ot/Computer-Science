#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "structures.h"

Node *init_node(char *string) {
  Node *node = malloc(sizeof(*node));

  node->id = 1;

  node->x = ((float) rand() / (float) RAND_MAX) * (1000 - 0) + 0;
  node->y = ((float) rand() / (float) RAND_MAX) * (1000 - 0) + 0;
  node->buffer = malloc(sizeof(Node) * 10);

  memcpy(node->data, string, sizeof(string));

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

int main(int argc, char *argv[]) {
  Node *node;
  char *packet;
  char *buffer;
  int length;

  char *f = "Hello";
  char *s = "World";

  buffer = append_byte_array(f, s, strlen(f), strlen(s));

  packet = create_packet(buffer, 16);
  length = parse_packet(packet, buffer);

  printf("%d\n", length);
  printf("%s\n", buffer);

  return EXIT_SUCCESS;
}