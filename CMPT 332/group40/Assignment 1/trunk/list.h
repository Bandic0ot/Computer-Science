#ifndef _LISTH_
#define _LISTH_

typedef struct NODE{
    void *item;
    struct NODE *next;
    struct NODE *prev;
} NODE;
typedef struct LIST{
    struct NODE *head;
    struct NODE *cur;
    struct NODE *tail;
    int size;
} LIST;

#endif 


