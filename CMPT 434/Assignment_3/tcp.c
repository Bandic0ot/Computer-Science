#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "tcp.h"

void create_connection(char *address, char *port, int *sock) {
  int addrinfo_status;
  struct addrinfo hints, *results;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  addrinfo_status = getaddrinfo(address, port, &hints, &results);
  if(addrinfo_status != 0) {
    fprintf(stderr, "%s\n", gai_strerror(addrinfo_status));
    exit(EXIT_FAILURE);
  }

  for(struct addrinfo *r = results; r != NULL; r = r->ai_next) {
    *sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol);

    if(*sock == -1) {
      perror("Socket");
      exit(-1);
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
  }

  return;
}

void start_listen(int *listen_sock, char *port) {
  struct addrinfo hints, *results, *r;
  int addrinfo_status;
  char *address = malloc(sizeof(socklen_t));

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  addrinfo_status = getaddrinfo(NULL, port, &hints, &results);

  if(addrinfo_status != 0) {
    fprintf(stderr, "%s", gai_strerror(addrinfo_status));
    return;
  }

  for(r = results; r != NULL; r = r->ai_next) {
    // Create a socket for listening.
    *listen_sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol);

    if(*listen_sock == -1) {
      perror("Socket");
      exit(EXIT_FAILURE);
    }

    // Bind to the designated port.
    if(bind(*listen_sock, r->ai_addr, r->ai_addrlen) == -1) {
      perror("Bind");
      exit(EXIT_FAILURE);
    }

    if(r->ai_family == AF_INET) {
      inet_ntop(r->ai_family, &(((struct sockaddr_in *) r->ai_addr)->sin_addr), address, sizeof(address));
    } else {
      inet_ntop(r->ai_family, &(((struct sockaddr_in6 *) r->ai_addr)->sin6_addr), address, sizeof(address));
    }

    break;
  }

  if(r == NULL) {
    fprintf(stderr, "Failed to bind.\n");
    exit(EXIT_FAILURE);
  }

  freeaddrinfo(results);

  if(listen(*listen_sock, 10) == -1) {
    perror("Listen");
    exit(EXIT_FAILURE);
  }

  printf("Listening on %s, port %s...\n", address, port);
}

void handle_connection(int listen_sock) {
  while(1) {
    int node_sock;
    struct sockaddr_storage client_addr;
    socklen_t client_addrlen;

    client_addrlen = sizeof(socklen_t);
    node_sock = accept(listen_sock, (struct sockaddr *) &client_addr, &client_addrlen);

    if (node_sock == -1) {
      perror("Accepting connnection.");
      exit(EXIT_FAILURE);
    }

    if(fork() == 0) {
      close(listen_sock);
    }
  }
}

char *create_packet(char *data, uint32_t size) {
  uint32_t length;
  char *packet;

  length = htonl(sizeof(uint32_t) + size);

  packet = malloc(sizeof(uint32_t) + size);

  memmove(packet, &length, sizeof(uint32_t));
  memmove(&packet[sizeof(uint32_t)], data, size);

  return packet;
}

// Takes a packet and a buffer, returns the length of the packet
// and stores the data in buffer.
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

int unpack_packet_size(char *packet) {
  uint32_t packet_size;

  packet_size = 0;

  for(int i = 0; i < sizeof(uint32_t); i++) {
    packet_size += packet[i] << (i * 8);
  }

  packet_size = ntohl(packet_size);

  return packet_size;
}

void send_all(int sock, char *data, uint32_t size) {
  int bytes, bytes_sent, bytes_remaining, packet_size;
  char *packet;

  packet = create_packet(data, size);
  packet_size = size + sizeof(uint32_t);

  bytes_remaining = packet_size;
  bytes_sent = 0;

  while(bytes_sent < packet_size) {
    bytes = send(sock, &packet[bytes_sent], bytes_remaining, 0);
    bytes_sent += bytes;
    bytes_remaining -= bytes;

    if(bytes == -1) {
      perror("Send");
      exit(EXIT_FAILURE);
    }
  }
}

// Receives data from the specified socket and writes it to a buffer. 
// Returns the number of bytes recieved.
int recv_all(int sock, char *buffer, uint32_t size) {
  int bytes, bytes_recv, data_size;
  char packet_size_buffer[sizeof(uint32_t)];

  recv(sock, packet_size_buffer, sizeof(u_int32_t), 0);

  data_size = unpack_packet_size(packet_size_buffer) - sizeof(uint32_t);

  bytes_recv = 0;

  while(bytes_recv < data_size) {
    bytes = recv(sock, &buffer[bytes_recv], size, 0);
    bytes_recv += bytes;

    if(bytes == -1) {
      perror("Recv");
      exit(EXIT_FAILURE);
    } else if (bytes == 0) {
      printf("Connection closed.\n");
      exit(EXIT_FAILURE);
    }
  
  }

  return bytes_recv;
}

// Appends the second byte array to the first.
char *append_byte_array(char *byte1, char *byte2, uint32_t size1, uint32_t size2) {
  char *byte_array;

  byte_array = malloc(size1 + size2);

  memmove(byte_array, byte1, size1);
  memmove(&byte_array[size1], byte2, size2);

  return byte_array;
}