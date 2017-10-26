//list_adders.c

#include <stdio.h>
#include <stdlib.h>
#include "list.h"




//LIST *listCreate()
//pre: nothing
//post: makes an new, empty list, and returns its reference on success. Returns
// a NULL pointeron failure.
struct LIST *listCreate(){

    return NULL;
}


//int listAdd(list,item)
//pre: list - LIST*
//      item - void*
//post: adds the new item to the list directly after the current item, and
//makes the inserted item the current item. if the current pointer is at the
// end of the list, the item is added at the end. Return 0 on success, -1 on
//failure.
int listAdd(struct LIST *list, void *item){
    if(list == NULL || item == NULL){
        printf("insufficient list or item input in listAdd. \n");
 	return -1;
    }

    return 0;
}

//int listInsert(list, item)
//pre: list - LIST*
//      item - void*
//post:adds item to the list directly before the current item, and makes the
//new item the current one. if the current pointer is at the start of the list,
//the item is added at the end.
//return:   success = 0
//          failure = -1
int listInsert(struct LIST *list, void *item){
    if(list == NULL || item == NULL){
        printf("insufficient list or item input in listInsert. \n");
    	return -1;
    }
    return 0;
}

//int listAppend(list, item)
//pre: list - LIST*
//      item - void*
//post: adds item to the end of the list, and makes the new item the current
// one.
//return:   success = 0
//          failure = -1
int listAppend(struct LIST *list, void *item){
    if(list == NULL || item == NULL){
        printf("insufficient list or item input in listAppend. \n");
    	return -1;
    }
    return 0;
}


//int listPrepend(list, item)
//pre: list - LIST*
//      item - void*
//post: adds item to the front of the list, and makes the new item the current
// one.
//return:   success = 0
//          failure = -1
int listPrepend(struct LIST *list, void *item){
    if(list == NULL || item == NULL){
        printf("insufficient list or item input in listPrepend. \n");
    	return -1;
    }
    return 0;
}
