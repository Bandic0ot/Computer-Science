/*
* List library to be used in CMPT 332 in the Fall 2017 Term at the University
* of Saskatchewan. This code is not to be redistributed without permission of
* the authors.
*
* Authors: Derek Perrin, Dominic McKeith
*/
#define NO_CVS 7

void MonEnter(void);
void MonLeave(void);
void MonWait(int);
void MonSignal(int);
void MonInit(void);
