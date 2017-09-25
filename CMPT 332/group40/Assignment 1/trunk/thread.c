#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <windows.h>

#include "thread.h"

bool gKeepRunning = true;
int call_count = 0;

/* Main code for threads */
int child_main(int size) {
  printf("%d", GetCurrentThreadId());
  square(size);

  /* Thread is signaled to exit by parent. */
  if(gKeepRunning == false) {
    thread_exit();
  }

  return 0;
}

/* Main code for parent thread */
int parent_main(int num_threads, int deadline, int int_size)
{
  int i;
  struct thread_info *threads;
  int counter_array[num_threads];

  threads = malloc(num_threads * sizeof(struct thread_info));
  if (threads == NULL) exit(1);

  for (i = 0; i < num_threads; i++) {
    threads[i].entry = child_main;
    threads[i].size = int_size;
    thread_create(&threads[i]);
    counter_array[i] = threads[i].id;
  }

  /* Sleep this thread until the deadline */
  printf("Sleeping parent thread...\n");
  thread_sleep(deadline);

  gKeepRunning = false;

  /*for (i = 0; i < num_threads; i++) {
  printf("Thread %d executed the square() function 0 times.\n", deadline);
}*/

printf("All %d threads finished\n", num_threads);

return 0;
}

int square(int n) {
  call_count++;

  if(gKeepRunning == false) {
    return 0;
  }

  if (n == 0) {
    printf("Thread done!\n");
    return(0);
  }

  return(square(n-1) + n + n - 1);
}
