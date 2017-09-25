//
//Sean Robson-Kullman
//skr519
//11182480
//Matthew Mulenga
//mam558
//11144528




//mytestlist.c
#ifndef VARS_NEEDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

#endif






int main(){
       
    
    int bestNumber = 18;
    struct LIST *list = listCreate();
    void *trash;
 /////////////////////////////////////////  
 //

   list->size = 0;
   

   
   
   
   
 //////////////////////////////////////////////////////////
 // testing for functions from list_adders.c
 	
    int var = 4;
    var = listAdd(list, &bestNumber);
    assert(var == 0);
    printf("listAdd should print out an error message.\n");
    var = listAdd(NULL,&bestNumber);
    assert(var == -1); 

    var = 4;
    var = listInsert(list,&bestNumber);
    assert(var == 0);
    var = 4;
    printf("listInsert should print out an error message.\n");
    var = listInsert(NULL,&bestNumber);
    assert(var == -1);
    
    
    var = 4;
    var = listAppend(list,&bestNumber);
    assert(var == 0); 
    var = 4;
    printf("listAppend should print out an error message.\n");
    var = listAppend(NULL,&bestNumber);    
    assert(var == -1);

    var = 4;
    var = listPrepend(list,&bestNumber);
    assert(var == 0); 
    var = 4;
    printf("listPrepend should print out an error message.\n");
    var = listPrepend(NULL,&bestNumber);    
    assert(var == -1);

///////////////////////////////////////////////////////////
// testing for list_removers 

    listRemove(list);
    printf("listRemove should print out an error message.\n");
    listRemove(NULL);

    listFree(list,list);
    printf("listFree should print out an error message.\n");
    listFree(NULL, list);
    printf("listFree should print out another error message.\n");
    listFree(list, NULL);
    printf("listFree should print out another error message.\n");
    listFree(NULL,NULL);

    listTrim(list);
    printf("listTrim should print out an error message.\n");
    listTrim(NULL);

//////////////////////////////////////////////////////
// testing for list_movers

    trash = listFirst(list);
    printf("listFirst should print out an error message.\n");
    trash = listFirst(NULL);

    trash = listLast(list);
    printf("listLast should print out an error message.\n");
    trash = listLast(NULL);

    trash = listNext(list);
    printf("listNext should print out an error message.\n");
    trash = listNext(NULL);

    trash = listPrev(list);
    printf("listPrev should print out an error message.\n");
    trash = listPrev(NULL);
    
   // listSearch();

    var = listCount(list);
    printf("listCount should print out an error message.\n");
    var = listCount(NULL);

    trash = listCur(list);
    printf("listCur should print out an error message.\n");
    trash = listCur(NULL);
    
    listConcat(list,list);
    printf("listConcat should print out an error message.\n");
    listConcat(NULL, list);
    printf("listConcat should print out another error message.\n");
    listConcat(list,NULL);

    trash = &trash;
    
    return 0;
    
}






