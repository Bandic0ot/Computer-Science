#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "structures.h"
#include "tcp.h"

char recv_port[50];
uint32_t range, num_nodes;

void init_logger(int *listen_sock, char **args) {
  char *ptr;
  strcpy(recv_port, args[1]);

  range = strtol(args[2], &ptr, 10);
  num_nodes = strtol(args[3], &ptr, 10);

  start_listen(listen_sock, recv_port);
}

int main(int argc, char *argv[]) {
  int listen_sock;

  init_logger(&listen_sock, argv);

  return 0;
}