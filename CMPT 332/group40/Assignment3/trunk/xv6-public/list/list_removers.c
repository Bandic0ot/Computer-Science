/* Sean Robson-Kullman */
/* skr519 */
/* 11182480 */
/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


/* void *listRemove(list) 
 * pre: list - LIST* 
 * post: return current item, and take it out of the list. Make the next item
 * the current one. 
 * return: current item. 
 */
void *listRemove(struct LIST *list){
    	void *temp;
	struct NODE *trash;/*secont temp var*/
	if(list == NULL){/* when the list handed in does not exist */
        	printf("insufficient list input in listRemove. \n");
    		return NULL;
	}else if(list->cur == NULL){/* when the current node pointer is invalid */
		return NULL;
		printf("null current pointer");
	} else if (list->size == 0 ){/* when no elements in the list */
		printf("there are no elements in the list");	
		return NULL;	
	}

        trash = list->cur;
	temp = list->cur->item;/*initialize a temp variable*/

	if(list->size == 1){/* when one element in the list */
	
	list->cur = NULL;
	list->tail = NULL;
	list->head = NULL;
	/* dealocate node below */
	/* decrement size below */
		
	}else if(list->cur == list->tail){/* when the current element is the tail*/
		list->cur = list->cur->prev;/*move current node back one */
		list->cur->next = NULL;/*set the pointer "next" to null */
		list->tail = list->cur;/*set tail */
		/* trash->next->prev = list->cur; I dont know why i wrote this */
		/* decrement size below */
		/* head does not change */
		/* dealocate node bellow */

	}else if(list->head == list->cur){/* when the current node is the head*/
		list->cur = list->cur->next;/* move current node down one */
		list->cur->prev = NULL; /* set current's prev to NULL */
		list->head = list->cur;/* set new head to current*/
		/*decrement size below */
		/* tail does not change */
		/* dealocate node below */

	}else {/* when the node is not the first, last, ore only element */
		list->cur = list->cur->next;/* move cur node along */
		list->cur->prev = trash->prev; /* set new cur's prev pointer */
		trash->prev->next = list->cur; /* set the prev's next node */
		/*head is unchanged*/
		/*tail is unchanged*/
		/*dealocate node below*/
		/*decrement size below*/
	}

	list->size --;
	
	/* putting the removed node back on the empty node stack */
	EMPTYLIST[1].tail->next = trash;
	trash->prev = EMPTYLIST[1].tail;
	EMPTYLIST[1].tail = trash;
	trash->next = NULL;	
	EMPTYLIST[1].size ++;
	
   return temp;
}


/* void listFree(list,itemFree) 
 * pre: list1 - LIST* 
 *      itemFree - void* 
 * post: delete item. itemFree is a pointer to a routine tha frees an item. It
 * should be invoked(within listFree) as: (*itemFree)(itemToBeFreed)
 * return: nothing. 
 */
void listFree(struct LIST *list,void *itemFree){
    	int i = 0;
	if(list == NULL|| list->head == NULL||itemFree == NULL){
        	printf("insufficient list input in listFree. \n");
		return;
    	}if(list->size != 0){
		list->cur = list->head;
		i = 0;
		while (i < list->size){
			listRemove(list);
		}
	}
	listPrepend(&EMPTYLIST[0],list);
 	/* list = NULL; */
	return;
}


/* void *listTrim(list) 
 * pre: list - LIST* 
 * post: take last item out of the list, the current pointer shall be the new 
 * last item in the list. 
 * return: the last item.
 */ 
void *listTrim(struct LIST *list){
    	if(list == NULL){
        	printf("insufficient list input in listTrim. \n");
    		return NULL;
	}else if (list->size == 0){
		return NULL;
	}
	list->cur = list->tail;/* set the current item to the last node */
	return listRemove(list);/* remove the item */
}
