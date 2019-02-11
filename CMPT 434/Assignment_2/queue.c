#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX_DATA_SIZE 100

int count, head, tail, length;

// Initializes a queue for holding messages.
// Pre: A valid message buffer.
// Post: The buffer is set to the appropriate length and all queue values are initialized.
void initialize(int size) {
  length = size;
  count = 0;
  head = 0;
  tail = 0;
}

// Returns the max size of the queue.
int size() {
  return length;
}

// Checks if the queue is empty.
int empty() {
  if(count != 0) {
    return -1;
  }

  return 0;
}

int full() {
  if(count < length) {
    return -1;
  }

  return 0;
}

// Adds an item to the end of the queue.
void enqueue(char **queue, char *item) {
  if(count == size()) {
    printf("Queue is full.\n");

    return;
  }

  if(tail == size()) {
    tail = 0;
  }
  
  strcpy(queue[tail], item);

  tail++;
  count++;
}

// Removes an item from the end of the queue.
char *dequeue(char **queue) {
  char *item;

  if(empty() == 0) {
    printf("Queue is empty.\n");
    return NULL;
  }

  if(head == size()) {
    head = 0;
  }

  strcpy(item, queue[head]);

  head++;
  count--;

  return item;
}