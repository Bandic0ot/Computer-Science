//Sean Robson-Kullman
//skr519
//11182480
//Matthew Mulenga
//mam558
//11144528



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "thread.h"

int gKeepRunning = 1;
struct thread_info *threads;

/* Main code for threads */
int child_main(int size) {
  int start = get_systemtime();

  square(size);

  /* Thread is signaled to exit by parent. */
  if(gKeepRunning == 0) {
    for(int i = 0; i < size; i++) {
      if(get_threadId() == threads[i].id) {
        printf("Thread %d ran square %d times. Elapsed time: %dms\n",
        threads[i].id, threads[i].count,
        (get_systemtime() - start));
      }
    }
    thread_exit();
  }

  for(int i = 0; i < size; i++) {
    if(get_threadId() == threads[i].id) {
      printf("Thread %d ran square %d times. Elapsed time: %dms\n",
      threads[i].id, threads[i].count,
      (get_systemtime() - start));
    }
  }

  return 0;
}

/* Main code for parent thread */
int parent_main(int num_threads, int deadline, int int_size)
{
  int i;

  printf("%d, %d, %d\n", num_threads, deadline, int_size);

  threads = malloc(num_threads * sizeof(struct thread_info));
  if (threads == NULL) exit(1);

  for (i = 0; i < num_threads; i++) {
    threads[i].entry = child_main;
    threads[i].size = int_size;
    thread_create(&threads[i]);
  }

  /* Sleep this thread until the deadline */
  printf("Sleeping parent thread...\n");
  thread_sleep(deadline);
  printf("Deadline up!\n");
  gKeepRunning = 0;
  thread_sleep(1);

  return 0;
}

int square(int n) {

  if(gKeepRunning == 0) {
    return (0);
  }

  for(int i = 0; i < n; i++) {
    if(get_threadId() == threads[i].id) {
      threads[i].count++;
    }
  }

  if (n == 0) {
    return(0);
  }

  return(square(n-1) + n + n - 1);
}
