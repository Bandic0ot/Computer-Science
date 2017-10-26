/* Sean Robson-Kullman */
/* skr519 */
/* 11182480 */
/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

#include <stdlib.h>
#include <stdio.h>

#include <os.h>

#include "partA.h"

static void thread_wrapper(void *arg)
{
  struct thread_info *info = arg;
  info->id = (int) MyPid();

  StartETimer(info->id);
  Suspend();

  info->entry(info->size);

  Pexit();
}

int thread_create(struct thread_info *info)
{
  PID *thread;

  thread = malloc(sizeof(PID));
  info->thread = thread;
  info->count = 0;
  *thread = Create(thread_wrapper, 1500000, "child", info, NORM, USR);

  return 0;
}

void thread_sleep(int seconds)
{
  /* TICKINTERVAL is in microseconds */
  int ticks = (seconds * 1000000) / 10000;
  while (ticks > 0xffff) {
    Sleep(0xffff);
    ticks -= 0xffff;
  }

  Sleep(ticks);
}

void thread_exit() {
	Pexit();
}

void thread_resume(struct thread_info *info) {
	Resume(info->id);
}

int get_systemtime() {
	return (int) Time();
}

int get_threadId() {
	return (int) MyPid();
}

void thread_kill(struct thread_info *info) {
	if(PExists(info->id)) {
		printf("Killed. Thread %d ran square %d times. Elapsed time: %dms\n",
			info->id, info->count, GetETimer(info->id));

		Kill(info->id);
	}
}

static void parent_wrapper(void *arg)
{
  int *n;
  n = malloc(3 * sizeof(int));

  /* Okay. So what we're doing here is pretty wack. */
  /* First we create an array. Then we cast the void pointer 'arg' */
  /* as an integer pointer, which we then dereference and assign it to the */
  /* first element in the array. The addition in the following line aka n[1] */
  /* increments arg to the next element. 'arg' points to n[0] in mainp */
  /* so incrementing it means we're just selecting the next element of n[0] */
  /* in mainp. Got it? Don't worry, me neither. */
  /* Ps. I didn't even get it right after that explanation, I had to add */
  /* more brackets... MORE GODDAMN BRACKETS. So that the addition would be */
  /* applied to the pointer itself, not the dereferenced pointer. Sheesh. */
  /* What a day. */
  n[0] = *(int *) arg;
  n[1] = *((int *) arg + 1);
  n[2] = *((int *) arg + 2);

  parent_main(n[0], n[1], n[2]);
  Pexit();
}

int mainp(int argc, char*argv[]) {
  int *n;
  n = malloc(3 * sizeof(int));

  if (argc != 4) {
    printf("usage: %s <threads> <deadline> <size>\n", argv[0]);
    exit(1);
  }

  /* Store our 3 parameters. */
  n[0] = atoi(argv[1]);
  n[1] = atoi(argv[2]);
  n[2] = atoi(argv[3]);

  if (n[0] < 1) {
    printf("<threads> must be 1 or greater\n");
    exit(1);
  }

  if (n[1] < 1) {
    printf("<deadline> must be 1 or greater\n");
    exit(1);
  }
  if (n[2] < 1) {
    printf("<size> must be 1 or greater\n");
    exit(1);
  }

  Create(parent_wrapper, 1500000, "main", n, NORM, USR);

  return 0;
}
