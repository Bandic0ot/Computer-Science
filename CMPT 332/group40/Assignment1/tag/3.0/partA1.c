/* Sean Robson-Kullman */
/* skr519 */
/* 11182480 */
/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

#include <stdlib.h>
#include <stdio.h>

#include <windows.h>

#include "partA.h"

/* Taken from week1-threads material. */
static DWORD WINAPI thread_wrapper(void *arg)
{
  struct thread_info *info = arg;
  info->entry(info->size);
  return 0;
}

int thread_create(struct thread_info *info)
{
  HANDLE *thread;
  DWORD thread_id;

  thread = malloc(sizeof(HANDLE));
  info->thread = thread;
  *thread = CreateThread(NULL, 1500000, thread_wrapper, info, 0, &thread_id);
  info->id = (int) thread_id;
  info->count = 0;

  return 0;
}

void thread_sleep(int seconds)
{
  Sleep(seconds * 1000);
}

void thread_exit() {
	DWORD exit_code = 0;

  ExitThread(exit_code);
}

void thread_resume(struct thread_info *info) {
	ResumeThread(info->thread);
}

int get_systemtime() {
	int s;
	int ms;
	int total;
	SYSTEMTIME time;

	GetSystemTime(&time);

	s = time.wSecond * 1000;
	ms =  time.wMilliseconds;
	total = s + ms;

	return total;
}

int get_threadId() {
	return GetCurrentThreadId();
}

void thread_kill(struct thread_info *info) {
  /* This does nothing in windows as it's not needed for the way we */
  /* implement signalling the children to exit. */
}

int main(int argc, char *argv[]) {
  int threads;
  int deadline;
  int size;

  if (argc != 4) {
    printf("usage: %s <threads> <deadline> <size>\n", argv[0]);
    exit(1);
  }

  threads = atoi(argv[1]);
  deadline = atoi(argv[2]);
  size = atoi(argv[3]);

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

  parent_main(threads, deadline, size);

  return 0;
}
