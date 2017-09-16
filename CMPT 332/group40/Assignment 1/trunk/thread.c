#include <stdlib.h>
#include <stdio.h>

#include "thread.h"

int main(int argc, char *argv[]) {
  struct thread_info *n_thread;

  // Modified from week1-threads material.
  // Check to make sure 3 arguments are passed.
  if(argc != 4) {
    printf("Usage: %s <THREADS> <DEADLINE> <SIZE>\n", argv[0]);
    exit(1);
  }

  int threads_argument = atoi(argv[1]);
  int deadline_argument = atoi(argv[2]);
  int size_argument = atoi(argv[3]);


  // Test all the thread functions to see if they check for valid parameters.
  thread_create(n_thread);
  thread_sleep(deadline_argument);
  thread_exit();
  thread_kill(5);

  return 0;
}
