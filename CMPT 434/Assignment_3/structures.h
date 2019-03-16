#ifndef structures
#define structures

typedef struct Node {
  uint32_t id, distance;
  char data[10], recv_port[50], log_hostname[50], log_port[50];
  float x, y;
  struct Node *buffer;
} Node;

#endif //structures