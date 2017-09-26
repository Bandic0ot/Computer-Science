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

struct hash {
  int thread_id;
  int count;
};

int gKeepRunning = 1;
struct hash *counter_array;

/* Main code for threads */
int child_main(int size) {
  int start = get_systemtime();

  square(size);

  /* Thread is signaled to exit by parent. */
  if(gKeepRunning == 0) {
    for(int i = 0; i < size; i++) {
      if(get_threadId() == counter_array[i].thread_id) {
        printf("Thread %d ran square %d times. Elapsed time: %dms\n",
        counter_array[i].thread_id, counter_array[i].count,
        (get_systemtime() - start));
      }
    }
    thread_exit();
  }

  for(int i = 0; i < size; i++) {
    if(get_threadId() == counter_array[i].thread_id) {
      printf("Thread %d ran square %d times. Elapsed time: %dms\n",
      counter_array[i].thread_id, counter_array[i].count,
      (get_systemtime() - start));
    }
  }

  return 0;
}

/* Main code for parent thread */
int parent_main(int num_threads, int deadline, int int_size)
{
  int i;
  struct thread_info *threads;

  counter_array = malloc(int_size * sizeof(struct hash));
  threads = malloc(num_threads * sizeof(struct thread_info));
  if (threads == NULL) exit(1);

  for (i = 0; i < num_threads; i++) {
    threads[i].entry = child_main;
    threads[i].size = int_size;
    thread_create(&threads[i]);

    /* Initialize the counting array */
    counter_array[i].thread_id = threads[i].id;
    counter_array[i].count = 0;
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
    if(get_threadId() == counter_array[i].thread_id) {
      counter_array[i].count++;
    }
  }

  if (n == 0) {
    return(0);
  }

  return(square(n-1) + n + n - 1);
}
