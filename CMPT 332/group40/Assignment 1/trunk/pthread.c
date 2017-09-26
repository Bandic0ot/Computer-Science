
//Sean Robson-Kullman
//skr519
//11182480
//Matthew Mulenga
//mam558
//11144528



#include <stdlib.h>
#include <stdio.h>

#include <os.h>

#include "thread.h"

static void thread_wrapper(void *arg)
{
  struct thread_info *info = arg;
  info->entry(info->id);
  Pexit();
}

int thread_create(struct thread_info *info)
{
  PID *thread;

  thread = malloc(sizeof(PID));
  info->thread = thread;
  *thread = Create(thread_wrapper, 4096, "dummy", info, NORM, USR);

  return 0;
}

void thread_sleep(int seconds)
{
  /* TICKINTERVAL is in microseconds */
  int ticks = (seconds * 1000000);
  while (ticks > 0xffff) {
    Sleep(0xffff);
    ticks -= 0xffff;
  }

  Sleep(ticks);
}

int thread_join(struct thread_info *info)
{
  PID *thread;

  thread = info->thread;
  /* busy ish wait... */
  while (PExists(*thread)) {
    Sleep(1);
  }

  return 0;
}

void thread_exit() {
	Pexit();
}

void thread_resume(struct thread_info *info) {
	Resume(info->thread)
}

int get_systemtime() {

	return 0;
}

int get_threadId() {
	return (int) MyPid();
}

static void parent_wrapper(void *arg)
{
  int n = *(int *) arg;
  parent_main(n, 0, 0);
  Pexit();
}

int mainp(int argc, char*argv[]) {
  int *n;

  if (argc != 4) {
    printf("usage: %s <threads> <deadline> <size>\n", argv[0]);
    exit(1);
  }

  n = malloc((argc - 1) * sizeof(int));
  n[0] = atoi(argv[1]);
  n[1] = atoi(argv[2]);
  n[2] = atoi(argv[3]);


  if (threads < 1) {
    printf("<threads> must be 1 or greater\n");
    exit(1);
  }

  if (deadline < 1) {
    printf("<deadline> must be 1 or greater\n");
    exit(1);
  }
  if (size < 1) {
    printf("<size> must be 1 or greater\n");
    exit(1);
  }

  Create(parent_wrapper, 1500000, "main", n, NORM, USR);

  return 0;
}
