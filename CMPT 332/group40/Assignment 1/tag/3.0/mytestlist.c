/* Sean Robson-Kullman */
/* skr519 */
/* 11182480 */
/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

/* mytestlist.c */
#ifndef VARS_NEEDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

#endif


int comparator(void *item, void *item2){
	if (item ==NULL||item2==NULL){
		return 0;
	}
	if((*(int*)item) == (*(int *)item2)){
		return 1;
	}
	return 0;
}


struct LIST *addNtoList(struct LIST *list,int size){
	int i = 0;
	if (list == NULL)return NULL;
	while (i < size){
		listAppend(list,&i);
		i++;
	}
	return list;
}





int main(){
    int bestNumber = 18;
    int var;
    struct LIST *list = listCreate();
    void *trash;
    struct LIST *scrap;
 
    scrap = listCreate();
    if(scrap == NULL){
	printf("\n listCreate() allocated a list that does not exist.\n");
    }else{
	printf("\n listCreate() allocated a new list correctly.\n");
    }
    
 /*//////////////////////////////////////
 */

   list->size = 0;






 /*////////////////////////////////////////////////////////
  //testing for functions from list_adders.c
*/
   printf("\n list size: %d",list->size);
    var = 4;
    var = listAdd(list, &bestNumber);
    assert(var == 0);
    printf("\n listAdd should print out an error message.\n");
    var = listAdd(NULL,&bestNumber);
    assert(var == -1);

    printf("\n list size: %d",list->size);

    var = 4;
    var = listInsert(list,&bestNumber);
    assert(var == 0);
    var = 4;
    printf("\n listInsert should print out an error message.\n");
    var = listInsert(NULL,&bestNumber);
    assert(var == -1);

    printf("\n list size: %d",list->size);

    var = 4;
    var = listAppend(list,&bestNumber);
    assert(var == 0);
    var = 4;
    printf("\n listAppend should print out an error message.\n");
    var = listAppend(NULL,&bestNumber);
    assert(var == -1);

    printf("\n list size: %d",list->size);

    var = 4;
    var = listPrepend(list,&bestNumber);
    assert(var == 0);
    var = 4;
    printf("\n listPrepend should print out an error message.\n");
    var = listPrepend(NULL,&bestNumber);
    assert(var == -1);

    printf("\n list size: %d",list->size);
/*/////////////////////////////////////////////////////////
 //testing for list_removers
*/
    listRemove(list);
    printf("\n listRemove should print out an error message.\n");
    listRemove(NULL);

    printf("\n list size: %d \n",list->size);

    addNtoList(scrap,3);   
    listFree(scrap,&bestNumber);
    if(EMPTYLIST[0].head == NULL) printf("\n list deleted \n");
    

    printf("\n listFree should print out an error message.\n");
    listFree(NULL, list);
    printf("\n listFree should print out another error message.\n");
    listFree(list, NULL);
    printf("\n listFree should print out another error message.\n");
    listFree(NULL,NULL);

    printf("\n list size: %d",list->size);

    listTrim(list);
    printf("\n listTrim should print out an error message.\n");
    listTrim(NULL);

    printf("\n list size: %d",list->size);
/*////////////////////////////////////////////////////
// testing for list_movers
*/

    trash = listFirst(list);
    printf("\n listFirst should print out an error message.\n");
    trash = listFirst(NULL);

    trash = listLast(list);
    printf("\n listLast should print out an error message.\n");
    trash = listLast(NULL);

    trash = listNext(list);
    printf("\n listNext should print out an error message.\n");
    trash = listNext(NULL);

    trash = listPrev(list);
    printf("\n listPrev should print out an error message.\n");
    trash = listPrev(NULL);

    printf("\n size of list: %d\n",list->size);
    
    /* test for and element that is not in the list */
    if (listSearch(list,comparator,(&var))){
	    printf("\n item found by listSearch\n");
    }else {
	    printf("\n item not found by listSearch\n");
    }
    /* test for when the current item is the tail. */
    if (listSearch(list,comparator,(&bestNumber))){
            printf("\n item found by listSearch\n");
    }else {
            printf("\n item not found by listSearch\n");
    }
    
    listFirst(list);
    /* test for an element that should be found. */
    if (listSearch(list,comparator,(&bestNumber))){
            printf("\n item found by listSearch\n");
    }else {
            printf("\n item not found by listSearch\n");
    }


    var = listCount(list);
    printf("\n listCount should print out an error message.\n");
    var = listCount(NULL);

    trash = listCur(list);
    printf("\n listCur should print out an error message.\n");
    trash = listCur(NULL);

    listConcat(list,list);
    printf("\n listConcat should print out an error message.\n");
    listConcat(NULL, list);
    printf("\n listConcat should print out another error message.\n");
    listConcat(list,NULL);

    trash = &trash;

    return 0;

}
