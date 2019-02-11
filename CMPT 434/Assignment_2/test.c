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

void serialize_frame(int s, int a, char *data, int length, char *buffer) {
  uint32_t seq_num = htonl(s);
  uint32_t ack = htonl(a);
  uint32_t len = htonl(length);

  memcpy(buffer, &seq_num, sizeof(uint32_t));
  memcpy(&buffer[sizeof(uint32_t)], &ack, sizeof(uint32_t));
  memcpy(&buffer[sizeof(uint32_t) * 2], &len, sizeof(uint32_t));
  memcpy(&buffer[sizeof(uint32_t) * 3], data, length);
}

void unserialize_frame(int *s, int *a, int *length, char *buffer) {
  *s = ntohl(buffer[0] + (buffer[1] << 8) + (buffer[2] << 16) + (buffer[3] << 24));
  *a = ntohl(buffer[4] + (buffer[5] << 8) + (buffer[6] << 16) + (buffer[7] << 24));
  *length = ntohl(buffer[8] + (buffer[9] << 8) + (buffer[10] << 16) + (buffer[11] << 24));
}

int main(int argc, char **argv) {
  char buffer[MAX_DATA_SIZE];
  char s[50];

  int seq, ack, len;

  strcpy(s, "Hello");

  serialize_frame(8, 78, s, strlen(s), buffer);
  unserialize_frame(&seq, &ack, &len, buffer);

  printf("%d %d %d", seq, ack, len);

  return 0;
}