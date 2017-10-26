#include <stdlib.h>
#include <stdio.h>

#include <kernel.h>

#include "thread.h"

// Create a new thread.
int thread_create(struct thread_info *info) {
  if(1 == 1) {
    printf("Got to procedure 'thread_create'.\n");
  } else {
    printf("Error in procedure 'thread_create': invalid parameter 'thread_info *'.\n");
  }

  return 0;
}

// Tell a thread to sleep.
void thread_sleep(int deadline) {
  if(deadline > 0) {
    printf("Got to procedure 'thread_sleep'.\n");
  } else {
    printf("Error in procedure 'thread_sleep': invalid parameter 'deadline'.\n");
  }
}

// Exit from a thread.
void thread_exit() {
  printf("Got to procedure 'thread_exit'.\n");
}

// Kill another thread.
int thread_kill(int pid) {
  if(pid > 0) {
    printf("Got to procedure 'thread_kill'.\n");
  } else {
    printf("Error in procedure 'thread_kill': invalid parameter 'pid'.\n");
  }


  return 0;
}
