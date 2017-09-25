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

int square(int n);


#endif /* _THREAD_H_ */
