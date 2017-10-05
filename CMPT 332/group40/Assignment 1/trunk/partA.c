/* Sean Robson-Kullman */
/* skr519 */
/* 11182480 */
/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "partA.h"

int gKeepRunning = 1;
int *number_of_threads;
struct thread_info *threads;

/* Main code for threads */
int child_main(int size) {
  int i;
  int end;
  int start;

  start = get_systemtime();

  square(size);

  end = get_systemtime();

  /* Thread is signaled to exit by parent. */
  if(gKeepRunning == 0) {
    for(i = 0; i < *number_of_threads; i++) {
      if(get_threadId() == threads[i].id) {
        printf("Killed. Thread %d ran square %d times. Elapsed time: %dms\n",
        threads[i].id, threads[i].count , (end - start));
      }
    }
    thread_exit();
  }

  for(i = 0; i < *number_of_threads; i++) {
    if(get_threadId() == threads[i].id) {
      printf("Thread %d ran square %d times. Elapsed time: %dms\n",
      threads[i].id, threads[i].count, (end - start));
    }
  }

  return 0;
}

/* Main code for parent thread */
int parent_main(int num_threads, int deadline, int int_size)
{
  int i;
  number_of_threads = &num_threads;

  threads = malloc(num_threads * sizeof(struct thread_info));
  if (threads == NULL) exit(1);

  for (i = 0; i < num_threads; i++) {
    threads[i].entry = child_main;
    threads[i].size = int_size;
    thread_create(&threads[i]);
  }

  /* Sleep this thread until the deadline */
  printf("Sleeping parent thread...\n");
  for (i = 0; i < num_threads; i++) {
	  thread_resume(&threads[i]);
  }
  thread_sleep(deadline);
  printf("Deadline up!\n");

  /* Kill all the running child threads. */
  for(i = 0; i < num_threads; i++) {
	  thread_kill(&threads[i]);
  }

  gKeepRunning = 0;
  thread_sleep(1);

  return 0;
}

int square(int n) {
  int i;

  if(gKeepRunning == 0) {
    return (0);
  }

  if (n == 0) {
    return(0);
  }

  /* Increment the current threads call count. */
  for(i = 0; i < *number_of_threads; i++) {
    if(get_threadId() == threads[i].id) {
      threads[i].count++;
    }
  }

  return(square(n-1) + n + n - 1);
}
