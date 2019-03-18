#ifndef structures
#define structures

typedef struct Node {
  uint32_t id, x, y, distance;
  char data[11], recv_port[50], log_hostname[50], log_port[50]; // One byte in data[11] reserved for null character.
  struct Node *buffer;
} Node;

#endif //structures