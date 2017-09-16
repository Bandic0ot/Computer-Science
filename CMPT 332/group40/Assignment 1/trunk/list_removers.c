
#include <stdio.h>
#include <stdlib.h>
#include "list.h"






//void *listRemove(list)
//pre: list - LIST*
//post: return current item, and take it out of the list. Make the next item
//the current one.
//return: current item.
void *listRemove(struct LIST *list){
    if(list == NULL){
        printf("insufficient list input in listRemove. \n");
    }
   return 0;
}


//void listFree(list,listFree)
//pre: list1 - LIST*
//      list2 - LIST*
//post: delete item. itemFree is a pointer to a routine tha frees an item. It
//should be invoked(within listFree) as: (*itemFree)(itemToBeFreed);
//return: nothing.
void listFree(struct LIST *list,struct LIST *listFree){
    if(list == NULL || listFree ==NULL){
        printf("insufficient list input in listFree. \n");
    }
}


//void *listTrim(list)
//pre: list - LIST*
//post: take last item out of the list, the current pointer shall be the new
//last item in the list.
//return: the last item.
void *listTrim(struct LIST *list){
    if(list == NULL){
        printf("insufficient list input in listTrim. \n");
    }
    return 0;
}
