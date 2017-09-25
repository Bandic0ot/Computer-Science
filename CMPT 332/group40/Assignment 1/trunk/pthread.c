#include <stdlib.h>
#include <stdio.h>

#include <kernel.h>

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
    int ticks = (seconds * 1000000) / TICKINTERVAL;
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

static void parent_wrapper(void *arg)
{
    int n = *(int *) arg;
    parent_main(n);
    Pexit();
}

  return 0;
}
