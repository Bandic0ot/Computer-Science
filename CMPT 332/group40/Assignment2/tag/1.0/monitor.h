/*
 * monitor.h
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
void MonEnter();


/* MonLeave()
 * pre:	nothing
 * post:
 *
 *  Release a lock
 *
 * return: nothing
 */
void MonLeave();


/* MonWait(state)
 * pre: semaphor(integer)
 * post: 
 *
 * waits until the state is signaled
 * then continues
 *
 * return: nothing
 */
void MonWait(int state);


/* MonSignal(state)
 * pre: semaphor(integer)
 * post:
 *
 * signals the state to waiting processes
 * 
 * return: nothing
 */
void MonSignal(int state);


/* MonInit()
 * pre: nothing
 * post:
 *
 * initiates the monitor
 *
 * return: nothing
 */
void MonInit();



