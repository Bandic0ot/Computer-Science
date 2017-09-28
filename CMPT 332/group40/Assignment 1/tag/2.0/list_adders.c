
//Sean Robson-Kullman
//skr519
//11182480
//Matthew Mulenga
//mam558
//11144528




//list_adders.c
#ifndef VARS_NEEDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct LIST *EMPTYLIST = NULL;
struct NODE *EMPTYNODE = NULL;
int MIN_NODE_SIZE = 20;
int MIN_LIST_SIZE = 10;
#endif


//LIST *listCreate()
//pre: nothing
//post: makes an new, empty list, and returns its reference on success. Returns
// a NULL pointeron failure.
struct LIST *listCreate(){
    int i = 2;
    if(EMPTYLIST == NULL){
        
        // allocate memory to global variables EMPTYLIST and EMPTYNODE
        EMPTYLIST = malloc(MIN_LIST_SIZE*sizeof(struct LIST)); 
        EMPTYNODE = malloc(MIN_NODE_SIZE*sizeof(struct NODE));
        
        //store all (empty) lists in the 0 list.
        EMPTYLIST[0].head = &EMPTYNODE[0];
        EMPTYLIST[0].cur = NULL;
        EMPTYLIST[0].tail = &EMPTYNODE[0];
        
        while(i<MIN_LIST_SIZE){
            //allocating pointers for the list of empty lists.
            EMPTYNODE[i-2].item = &EMPTYLIST[i];
            EMPTYNODE[i-2].prev = EMPTYLIST[0].cur;
            EMPTYLIST[0].tail->next = &EMPTYNODE[i-2];
            
            EMPTYLIST[0].cur = &EMPTYNODE[i-2];
            EMPTYLIST[0].tail = &EMPTYNODE[i-2];
                
                
            EMPTYLIST[0].size ++;
            i++;
        }
        
        //store all (empty) lists in the 0 list.
        EMPTYLIST[1].head = &EMPTYNODE[i-2];
        EMPTYLIST[1].cur = NULL;
        EMPTYLIST[1].tail = &EMPTYNODE[i-2];
        i = i-2;
        
        //store all (empty) nodes into the 1 list.
        while(i<MIN_NODE_SIZE){
            //allocating pointers for the list of empty nodes.
            EMPTYNODE[i].item = NULL;
            EMPTYNODE[i].prev = EMPTYLIST[1].cur;
            EMPTYLIST[1].tail->next = &EMPTYNODE[i];
            
            EMPTYLIST[1].cur = &EMPTYNODE[i];
            EMPTYLIST[1].tail = &EMPTYNODE[i];
            
            
            EMPTYLIST[1].size ++;
            i++;
        }
    }
    if(EMPTYLIST[0].size == 0){
        return NULL;
    }
    //remove the tail element from emptylist[0]. return item from that node.
    struct LIST *temp = NULL;
    temp = EMPTYLIST[0].tail->item;
    EMPTYLIST[1].cur = EMPTYLIST[1].tail;
    EMPTYLIST[1].tail = EMPTYLIST[0].tail;
    EMPTYLIST[0].tail = EMPTYLIST[1].tail->prev;
    EMPTYLIST[0].tail->next = NULL;
    EMPTYLIST[0].cur = EMPTYLIST[0].tail;
    
    EMPTYLIST[1].tail->prev = EMPTYLIST[1].cur;
    
    return temp;
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
    struct NODE *temp = NULL;
    temp = EMPTYLIST[1].tail;
    temp->item = item;
    //swap the new node out of the empty node list.
    EMPTYLIST[1].tail = EMPTYLIST[1].tail->prev;
    EMPTYLIST[1].tail->next = NULL;
    EMPTYLIST[1].tail->item = item;
    EMPTYLIST[1].size --;
    EMPTYLIST[1].cur = EMPTYLIST[1].tail;
    
    
    if(list->size == 0){
        list->head = temp;
        list->tail = temp;
        list->cur = temp;
        temp->next = NULL;
        temp->prev = NULL;
        list->size ++;
        return 0;
    }
    if(list->cur == list->tail){
        temp->prev = list->cur;
        temp->next = NULL;
        list->cur->next = temp;
        list->cur = temp;
        list->tail = temp;
        return 0;
    }
    temp->next = list->cur->next;
    temp->prev = list->cur;
    
    list->cur->next = temp;
    temp->next->prev = temp;
    list->size ++;
    
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
    if(list == NULL){
        printf("insufficient list input in listInsert. \n");
    	return -1;
    }
    struct NODE *temp = NULL;
    temp = EMPTYLIST[1].tail;
    temp->item = item; //set item to be in then new node.
    
    //swap the new node out of the empty node list.
    EMPTYLIST[1].tail = EMPTYLIST[1].tail->prev;
    EMPTYLIST[1].tail->next = NULL;
    EMPTYLIST[1].tail->item = item;
    EMPTYLIST[1].size --;
    EMPTYLIST[1].cur = EMPTYLIST[1].tail;
    
    if(list->size == 0){//if there is an empty list.
        temp->prev = NULL;
        temp->next = NULL;
        list->head = temp;
        list->tail = temp;
        list->cur = temp;
        list->size ++;
        return 0;
    }
    if(list->cur == list->head){//if it is the first element.
        temp->prev = NULL;
        temp->next = list->cur;
        list->head = temp;
        list->cur = temp;
        list->size ++;
        return 0;
    }
    temp->prev = list->cur->prev;
    temp->next = list->cur;
    list->cur = temp;
    list->size ++;
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
    list->cur = list->tail;
    int val = listAdd(list,item);
    
    return val;
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
    list->cur = list->head;
    int val = listInsert(list,item);
    return val;
}
