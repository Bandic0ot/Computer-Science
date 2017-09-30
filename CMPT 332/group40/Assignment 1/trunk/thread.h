//Sean Robson-Kullman
//skr519
//11182480
//Matthew Mulenga
//mam558
//11144528

#ifndef _THREAD_H_
#define _THREAD_H_

/* Modified from week1-threads tutorial material. */
typedef int(*thread_entry)(int);

/* Store information for thread */
struct thread_info {
  int id;
  thread_entry entry;
  void *thread; /* point to arch specific thread info */
  int size;
  int count; /* Counts how many times the thread has called square function. */
};


/* Create a thread */
int thread_create(struct thread_info *);

/* Create the parent thread */
int parent_main(int num_threads, int deadline, int int_size);

/* Join a thread */
int thread_join(struct thread_info *);

/* Sleep for a thread */
void thread_sleep(int deadline);

/* Exit a thread */
void thread_exit();

/* Resume a thread */
void thread_resume(struct thread_info *);

/* Retrieve the current threads ID */
int get_threadId();

int get_systemtime();

int square(int n);


#endif /* _THREAD_H_ */
