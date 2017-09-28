#include <stdio.h>
#include<stdlib.h>


#ifndef VARS_NEEDED
#define VARS_NEEDED

typedef struct NODE{
    void *item;
    struct NODE *next;
    struct NODE *prev;
}NODE;

typedef struct LIST{
    struct NODE *head;
    struct NODE *cur;
    struct NODE *tail;
    int size;
}LIST;

struct LIST *EMPTYLIST;
struct NODE *EMPTYNODE;
int MIN_NODE_SIZE;
int MIN_LIST_SIZE;

#endif    //VARS_NEEDED



//LIST *listCreate()
//pre: nothing
//post: makes an new, empty list, and returns its reference on success. Returns
// a NULL pointeron failure.
struct LIST *listCreate();


//int listAdd(list,item)
//pre: list - LIST*
//      item - void*
//post: adds the new item to the list directly after the current item, and
//makes the inserted item the current item. if the current pointer is at the
// end of the list, the item is added at the end. Return 0 on success, -1 on
//failure.
int listAdd(struct LIST *list, void *item);


//int listInsert(list, item)
//pre: list - LIST*
//      item - void*
//post:adds item to the list directly before the current item, and makes the
//new item the current one. if the current pointer is at the start of the list,
//the item is added at the end.
//return:   success = 0
//          failure = -1
int listInsert(struct LIST *list, void *item);


//int listAppend(list, item)
//pre: list - LIST*
//      item - void*
//post: adds item to the end of the list, and makes the new item the current
// one.
//return:   success = 0
//          failure = -1
int listAppend(struct LIST *list, void *item);


//int listPrepend(list, item)
//pre: list - LIST*
//      item - void*
//post: adds item to the front of the list, and makes the new item the current
// one.
//return:   success = 0
//          failure = -1
int listPrepend(struct LIST *list, void *item);


//void *listFirst(LIST list)
//pre: list- LIST*
//post: returns a pointer to the first item and makes the first item
//the current item.
void *listFirst(struct LIST *list);


//void *listLast(LIST list)
//pre: list- LIST*
//post: returns a pointer to the last item and makes the last item
//the current item.
void *listLast(struct LIST *list);


//void *listNext(LIST list)
//pre: list- LIST*
//post: Advances the list current item by one, and returns a pointer to
//the new current
//item. If this tries to advance past the end of the list, return NULL.
void *listNext(struct LIST *list);


//void *listPrev(LIST list)
//pre: list- LIST*
//post: backs up lists current item by one, and returns a pointer to the
//new current item.
//If this tries to advance past the end of the list, return NULL.
void *listPrev(struct LIST *list);


//void *listSearch(list, comparator, comparasonArg)
//pre: list - LIST*
//      comparator - function pointer
//      comparasonArg - void*
//post: searches list starting at the current item, until ether a match is
//found, or the end of the list is reached. pointer is left at the matched
// item or the end of the list.
//return: if no match found, return NULL. else, return pointer to the item
// that was found.
void *listSearch(struct LIST *list, int comparator(void *item1, void *item2), void *comparatorArg);


//int listCount(LIST list)
//pre: list- List*
//post: returns the number of items list pointer.
int listCount(struct LIST *list);


//void *listCur(LIST *list)
//pre: list- LIST*
//post: returns a pointer to the current item int the list.
void *listCur(struct LIST *list);


// void listConcat(list1,list2)
// pre: list1 - LIST*
//      lsit2 - LIST*
// post: adds list2 to the end of list1. the current pointer is set to the
//current pointer of list1. list2 nolonger exists after operation.
//return: nothing
void listConcat(struct LIST *list1,struct LIST *list2);


//void *listRemove(list)
//pre: list - LIST*
//post: return current item, and take it out of the list. Make the next item
//the current one.
//return: current item.
void *listRemove(struct LIST *list);


//void listFree(list,listFree)
//pre: list1 - LIST*
//      list2 - LIST*
//post: delete item. itemFree is a pointer to a routine tha frees an item. It
//should be invoked(within listFree) as: (*itemFree)(itemToBeFreed);
//return: nothing.
void listFree(struct LIST *list,struct LIST *listFree);


//void *listTrim(list)
//pre: list - LIST*
//post: take last item out of the list, the current pointer shall be the new
//last item in the list.
//return: the last item.
void *listTrim(struct LIST *list);






