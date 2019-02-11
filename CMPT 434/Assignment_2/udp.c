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

#define MAX_DATA_SIZE 100

// Attaches the sequence number, ack, and message length to the front of the frame.
// Pre: A valid message.
// Post: A message with the first four bytes now representing the length of the message.
void serialize_frame(int *s, int *a, char *data, int *data_len, char *buffer) {
  uint32_t seq_num = htonl(*s);
  uint32_t ack = htonl(*a);
  uint32_t len = htonl(*data_len);

  memcpy(buffer, &seq_num, sizeof(uint32_t));
  memcpy(&buffer[sizeof(uint32_t)], &ack, sizeof(uint32_t));
  memcpy(&buffer[sizeof(uint32_t) * 2], &len, sizeof(uint32_t));
  memcpy(&buffer[sizeof(uint32_t) * 3], data, *data_len);
}

// Parses the first twelve bytes of a message to retrieve the sequence number, ack, and message length.
// Pre: A valid message.
// Post: The length of the message is returned.
void unserialize_frame(int *s, int *a, int *data_len, char *buffer) {
  *s = ntohl(buffer[0] + (buffer[1] << 8) + (buffer[2] << 16) + (buffer[3] << 24));
  *a = ntohl(buffer[4] + (buffer[5] << 8) + (buffer[6] << 16) + (buffer[7] << 24));
  *data_len = ntohl(buffer[8] + (buffer[9] << 8) + (buffer[10] << 16) + (buffer[11] << 24));
}

// Ensures all of a frame is sent.
void send_frame(int sock, char *frame) {
  int bytes, bytes_sent, bytes_remaining;

  bytes_remaining = sizeof(frame);
  bytes_sent = 0;

  while(bytes_sent < sizeof(frame)) {
    bytes = send(sock, &frame[bytes_sent], bytes_remaining, 0);
    bytes_sent += bytes;
    bytes_remaining -= bytes;

    if(bytes == -1) {
      perror("Send");
      exit(EXIT_FAILURE);
    }
  }
}

// Ensures that all of a message is recieved.
int recv_frame(int sock, int *s, int *a, char *data, int *length) {
  int bytes, bytes_recv, msg_length;
  char control[sizeof(uint32_t) * 3];
  char buffer[MAX_DATA_SIZE - sizeof(uint32_t) * 3];

  recv(sock, control, sizeof(u_int32_t) * 3, 0);
  unserialize_frame(s, a, length, control);

  bytes_recv = 0;

  while(bytes_recv < *length) {
    bytes = recv(sock, &buffer[bytes_recv], sizeof(buffer), 0); // TODO
    bytes_recv += bytes;

    if(bytes == -1) {
      perror("Recv"); 
      exit(EXIT_FAILURE);
    } else if (bytes == 0) {
      printf("Connection closed.\n");
      exit(EXIT_FAILURE);
    }
  
  }

  buffer[bytes_recv] = '\0';

  return bytes_recv - 1;
}