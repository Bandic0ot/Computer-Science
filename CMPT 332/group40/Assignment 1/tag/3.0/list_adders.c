/* 
 * Sean Robson-Kullman
 * skr519 
 * 11182480
 * Matthew Mulenga 
 * mam558 
 * 11144528 
 */

/* 
 * list_adders.c
 */ 
#ifndef VARS_NEEDED

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct LIST *EMPTYLIST = NULL;
struct NODE *EMPTYNODE = NULL;
int MIN_NODE_SIZE = 20;
int MIN_LIST_SIZE = 10;
int CURRENT_NODE_SIZE = 0;
int CURRENT_LIST_SIZE = 0;
#endif


/* 
 * LIST *listCreate() 
 * pre: nothing
 * post: makes an new, empty list, and returns its reference on success. Returns
 * a NULL pointeron failure.
 */
struct LIST *listCreate(){
    	int i = 2;
	struct LIST *temp;
  
     	if(EMPTYLIST == NULL){
		
        	/* allocate memory to global variables EMPTYLIST and EMPTYNODE */
		CURRENT_NODE_SIZE += MIN_NODE_SIZE;
        	CURRENT_LIST_SIZE += MIN_LIST_SIZE;
        	EMPTYLIST = malloc(MIN_LIST_SIZE*sizeof(struct LIST));
        	EMPTYNODE = malloc(MIN_NODE_SIZE*sizeof(struct NODE));
		
		/* store all (empty) lists in the 0 list. */
        	EMPTYLIST[0].head = &EMPTYNODE[0];
        	EMPTYLIST[0].cur = NULL;
        	EMPTYLIST[0].tail = &EMPTYNODE[0];

        	while(i<MIN_LIST_SIZE){
            		/* changing pointers for the list of empty lists. */
            		EMPTYNODE[i-2].item = &EMPTYLIST[i];
            		EMPTYNODE[i-2].prev = EMPTYLIST[0].cur;
            		EMPTYLIST[0].tail->next = &EMPTYNODE[i-2];

            		EMPTYLIST[0].cur = &EMPTYNODE[i-2];
            		EMPTYLIST[0].tail = &EMPTYNODE[i-2];


            		EMPTYLIST[0].size ++;
            		i++;
		}
        	/* store all (empty) lists in the 0 list. */
        	EMPTYLIST[1].head = &EMPTYNODE[i-2];
        	EMPTYLIST[1].cur = NULL;
        	EMPTYLIST[1].tail = &EMPTYNODE[i-2];
        	EMPTYLIST[1].size = 0;
		i = i-2;

        	/* store all (empty) nodes into the 1 list. */
        	while(i<MIN_NODE_SIZE){
            	/* allocating pointers for the list of empty nodes. */
            	EMPTYNODE[i].item = NULL;
            	EMPTYNODE[i].prev = EMPTYLIST[1].cur;
            	EMPTYLIST[1].tail->next = &EMPTYNODE[i];

            	EMPTYLIST[1].cur = &EMPTYNODE[i];
       		EMPTYLIST[1].tail = &EMPTYNODE[i];
			
            	EMPTYLIST[1].size ++;
            	i++;

        	}
    	}
    	if(EMPTYLIST[0].size <= 0){
        	return NULL;
    	}
	 /* remove the tail element from emptylist[0]. return item from that node. */
    	temp = EMPTYLIST[0].tail->item;
	
	/* setting the current node pointer to the current tail */
    	EMPTYLIST[1].cur = EMPTYLIST[1].tail;

	/* the node list is taking the soon to be empty, empty list node */
	EMPTYLIST[1].tail = EMPTYLIST[0].tail;	  
		
	/* set the tail of the empty list to tail's previous */
	EMPTYLIST[0].tail = EMPTYLIST[0].tail->prev;
	
	if (EMPTYLIST[0].size > 1){
		/* detatch the last node from the 0 lists */
        	(*EMPTYLIST[0].tail).next = NULL;
	}

	/* set the current list as the last element in the 0 list */
    	EMPTYLIST[0].cur = EMPTYLIST[0].tail;

	/* decrement size of the 0 list */
    	EMPTYLIST[0].size --;

    	temp->size = 0;
    	temp->head = NULL;
    	temp->tail = NULL;
    	EMPTYLIST[1].tail->prev = EMPTYLIST[1].cur;

    	return temp;
}


/* int listAdd(list,item) 
 * pre: list - LIST* 
 *      item - void* 
 * post: adds the new item to the list directly after the current item, and 
 * makes the inserted item the current item. if the current pointer is at the 
 * end of the list, the item is added at the end. Return 0 on success, -1 on 
 * failure. 
 */
int listAdd(struct LIST *list, void *item){
    struct NODE *temp;
    if(list == NULL){
        printf("insufficient list input in listAdd. \n");
        return -1;
    }else if(EMPTYLIST[1].size == 0) return -1;
    temp = EMPTYLIST[1].tail;
    temp->item = item;
    /* swap the new node out of the empty node list.*/ 
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

/* int listInsert(list, item) 
 * pre: list - LIST*
 *      item - void* 
 * post:adds item to the list directly before the current item, and makes the 
 * new item the current one. if the current pointer is at the start of the list, 
 * the item is added at the end. 
 * return:   success = 0 
 *          failure = -1 
 */
int listInsert(struct LIST *list, void *item){
    struct NODE *temp;
    if(list == NULL){
        printf("insufficient list input in listInsert. \n");
    	return -1;
    }else if(EMPTYLIST[1].size == 0) return -1;
    temp = NULL;
    temp = EMPTYLIST[1].tail;
    temp->item = item; /* set item to be in then new node. */

    /* swap the new node out of the empty node list. */
    EMPTYLIST[1].tail = EMPTYLIST[1].tail->prev;
    EMPTYLIST[1].tail->next = NULL;
    EMPTYLIST[1].tail->item = item;
    EMPTYLIST[1].size --;
    EMPTYLIST[1].cur = EMPTYLIST[1].tail;

    if(list->size == 0){ /* if there is an empty list. */
        temp->prev = NULL;
        temp->next = NULL;
        list->head = temp;
        list->tail = temp;
        list->cur = temp;
        list->size ++;
        
    }else if(list->cur == list->head){ /* if it is the first element. */
        temp->prev = NULL;
        temp->next = list->head;
        list->head = temp;
        list->cur->prev = temp;
        list->size ++;
	list->cur = list->head;
        
    }else {
    	temp->prev = list->cur->prev;
    	temp->next = list->cur;
    	list->cur->prev->next = temp;
    	list->cur->prev = temp;
    	list->size ++;
    }
    return 0;
}

/* int listAppend(list, item) 
 * pre: list - LIST* 
 *      item - void* 
 * post: adds item to the end of the list, and makes the new item the 
 * current one. 
 * return:   success = 0 
 *          failure = -1 
 */
int listAppend(struct LIST *list, void *item){
    /* int val; */
    struct NODE *temp;
    if(list == NULL || item == NULL){
        printf("insufficient list or item input in listAppend. \n");
    	return -1;
    }
    /*
    *list->cur = list->tail;
    *val = listAdd(list,item);
    *list->size ++;
    *return val;
    */
    if(EMPTYLIST[1].size == 0) return -1;
    temp = NULL;
    temp = EMPTYLIST[1].tail;
    temp->item = item; /* set item to be in then new node. */

    /* swap the new node out of the empty node list. */
    EMPTYLIST[1].tail = EMPTYLIST[1].tail->prev;
    EMPTYLIST[1].tail->next = NULL;
    EMPTYLIST[1].tail->item = item;
    EMPTYLIST[1].size --;
    EMPTYLIST[1].cur = EMPTYLIST[1].tail;

    if(list->size == 0){ /* if there is an empty list. */
        temp->prev = NULL;
        temp->next = NULL;
        list->head = temp;
        list->tail = temp;
        list->cur = temp;
        list->size ++;

    }else {
        list->cur = list->tail;
	temp->prev = list->cur;
        temp->next = NULL;
        list->cur->next = temp;
        list->size ++;
	list->tail = temp;
	list->cur = temp;
    }
    return 0;
}


/* int listPrepend(list, item) 
 * pre: list - LIST* 
 *      item - void* 
 * post: adds item to the front of the list, and makes the new item the 
 * current one. 
 * return:   success = 0
 *          failure = -1 
 */
int listPrepend(struct LIST *list, void *item){
    int val;
    if(list == NULL || item == NULL){
        printf("insufficient list or item input in listPrepend. \n");
    	return -1;
    }
    list->cur = list->head;
    val = listInsert(list,item);
    if(list->head != list->cur){
	    list->head = list->cur;
    }
    return val;
}
