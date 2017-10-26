
//Sean Robson-Kullman
//skr519
//11182480
//Matthew Mulenga
//mam558
//11144528


//list_movers.c
#ifndef VARS_NEEDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#endif

//void *listFirst(LIST list)
//pre: list- LIST*
//post: returns a pointer to the first item and makes the first item
//the current item.
void *listFirst(struct LIST *list){
    if(list == NULL){
        printf("listFirst input is insufficient.\n");
        return 0;
    }
    return 0;
}




//void *listLast(LIST list)
//pre: list- LIST*
//post: returns a pointer to the last item and makes the last item
//the current item.
void *listLast(struct LIST *list){
    if(list == NULL){
        printf("listLast input is insufficient.\n");
        return 0;
    }
    return 0;
}


//void *listNext(LIST list)
//pre: list- LIST*
//post: Advances the list current item by one, and returns a pointer to
//the new current
//item. If this tries to advance past the end of the list, return NULL.
void *listNext(struct LIST *list){
    if(list == NULL){
        printf("listNext input is insufficient.\n");
        return 0;
    }
    return 0;
}

//void *listPrev(LIST list)
//pre: list- LIST*
//post: backs up lists current item by one, and returns a pointer to the
//new current item.
//If this tries to advance past the end of the list, return NULL.
void *listPrev(struct LIST *list){
    if(list == NULL){
        printf("listPrev input is insufficient.\n");
        return NULL;
    }
    return NULL;
}


//void *listSearch(list, comparator, comparasonArg)
//pre: list - LIST*
//      comparator - function pointer
//      comparasonArg - void*
//post: searches list starting at the current item, until ether a match is
//found, or the end of the list is reached. pointer is left at the matched
// item or the end of the list.
//return: if no match found, return NULL. else, return pointer to the item
// that was found.
void *listSearch(struct LIST *list, int comparator(void *item1, void *item2), void *comparatorArg){
    if(list == NULL){
        printf("listSearch list input is insufficient.\n");
    }else if(comparatorArg == NULL){
        printf("listSearch comparatorArg input is insufficient.\n");
    }else if(comparator == NULL){
        printf("listSearch comparator input is insufficient.\n");
    }

    return 0;
}



//int listCount(LIST list)
//pre: list- List*
//post: returns the number of items list pointer.
int listCount(struct LIST *list){
if(list == NULL){
        printf("insufficient list input in listCount. \n");
    }
    return 0;
}


//void *listCur(LIST *list)
//pre: list- LIST*
//post: returns a pointer to the current item int the list.
void *listCur(struct LIST *list){
    if(list == NULL){
        printf("insufficient list input in listFirst. \n");
    }
    return 0;
}


// void listConcat(list1,list2)
// pre: list1 - LIST*
//      lsit2 - LIST*
// post: adds list2 to the end of list1. the current pointer is set to the
//current pointer of list1. list2 nolonger exists after operation.
//return: nothing
void listConcat(struct LIST *list1,struct LIST *list2){
    if(list1 == NULL || list2 == NULL){
        printf("insufficient list input in listConcat. \n");
    }
}
