/*
 * Monitor.c
 *
 * Sean Robson-Kullman
 * 11182480
 * skr519
 *
 * Matthew Muulenga
 * 11144528
 * mam558
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <os.h>
#include <standards.h>

#include "list.h"

int mutex;
struct LIST* processList;
int curState;

/* MonEnter()
 * pre: nothing
 * post:
 *
 * aquire a lock
 *
 * return: nothing
 */
void MonEnter(){
	int *pid;
	int arg;
        pid = malloc(sizeof(int));
	*pid = MyPid();
	arg = size(processList);
	if(mutex || arg != 0){
		listInsert(processList,pid);
		Suspend();
		/*suspend current process*/
	}
	mutex = 1;
}

/* MonLeave()
 * pre:	nothing
 * post:
 *
 *  Release a lock
 *
 * return: nothing
 */
void MonLeave(){
    	int* temp;
    	int arg;
        arg = size(processList);
	if(arg == 0){
	    mutex = 0;
    	}else {
	    temp = listTrim(processList);
	    Resume((int)(*temp));
	}
}

/* MonWait(state)
 * pre: semaphor(integer)
 * post: 
 *
 * waits until the state is signaled
 * then continues
 *
 * return: nothing
 */
void MonWait(int state){
	int pid;
       pid = MyPid();
    while (state != curState){
	    /*do nothing*/
	    ReSleep(pid,5);
    }
    curState = 0;
    
}

/* MonSignal(state)
 * pre: semaphor(integer)
 * post:
 *
 * signals the state to waiting processes
 * 
 * return: nothing
 */
void MonSignal(int state){
   curState = state;
    
}

/* MonInit()
 * pre: nothing
 * post:
 *
 * initiates the monitor
 *
 * return: nothing
 */
void MonInit(){
    mutex = 0;
    curState = 0;
    processList = listCreate();   
}






