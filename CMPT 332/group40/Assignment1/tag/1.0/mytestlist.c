//mytestlist.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"








int main(){
    int maxListSize = 20;
    int maxNodeSize = 40;
    struct LIST *list = malloc(maxListSize*sizeof(LIST));
    struct NODE *node = malloc(maxNodeSize*sizeof(NODE));    

 /////////////////////////////////////////  
 //
   node[0].prev = NULL;
   node[0].next = NULL;
   node[0].item = 36;

   list[0].size = 10;
   list[0].head = 0;
   list[0].tail = 0;
   list[0].cur = 0;

   
   
   
   
 //////////////////////////////////////////////////////////
 // testing for functions from list_adders.c
 	
    int var = 4;
    var = listAdd(list[0],18);
    assert(var == 0);
    var = listAdd(NULL,18);
    assert(var == -1); 

    var = 4;
    var = listInsert(list[0],18);
    assert(var == 0);
    var = 4;
    var = listInsert(NULL,18);
    assert(var == -1);
    
    
    var = 4;
    var = listAppend(list[0],18);
    assert(var == 0); 
    var = 4;
    var = listAppend(NULL,18);    
    assert(var == -1);

    var = 4;
    var = listPrepend(list[0],18);
    assert(var == 0); 
    var = 4;
    var = listPrepend(NULL,18);    
    assert(var == -1);

///////////////////////////////////////////////////////////
// testing for list_removers 

    listRemove(list[0]);
    listRemove(NULL);

    listFree(list[0],list[0]);
    listFree(NULL, list[0]);
    listFree(list[0], NULL);
    listFree(NULL,NULL);

    listTrim(list[0]);
    listTrim(NULL);

//////////////////////////////////////////////////////
// testing for list_movers

    listFirst(list[0]);
    listFirst(NULL);

    listLast(list[0]);
    listLast(NULL);

    listNext(list[0]);
    listNext(NULL);

    listPrev(list[0]);
    listPrev(NULL);
    
   // listSearch();

    listCount(list[0]);
    listCount(NULL);

    listCur(list[0]);
    listCur(NULL);
    
    listConcat(list[0],list[0]);
    listConcat(NULL, list[0]);
    listConcat(list[0],NULL);

    
    return 0;
    
}






