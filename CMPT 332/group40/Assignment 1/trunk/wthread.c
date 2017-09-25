#include <stdlib.h>
#include <stdio.h>

#include <windows.h>

#include "thread.h"

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
  *thread = CreateThread(NULL, 2048, thread_wrapper, info, 0, &thread_id);
  info->id = (int) thread_id;

  return 0;
}

void thread_sleep(int seconds)
{
  Sleep(seconds * 1000);
  printf("Deadline up.\n");
}

int thread_join(struct thread_info *info)
{
  HANDLE *thread;

  thread = info->thread;
  WaitForSingleObject(*thread, INFINITE);

  return 0;
}

void thread_exit() {
	DWORD exit_code;

  printf("Exiting thread...\n");
  ExitThread(exit_code);
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
