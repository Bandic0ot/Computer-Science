/*
* List library to be used in CMPT 332 in the Fall 2017 Term at the University
* of Saskatchewan. This code is not to be redistributed without permission of
* the authors.
*
* Authors: Derek Perrin, Dominic McKeith
*/

#ifndef LIST_ALLOC_H
#define LIST_ALLOC_H

#include <stdio.h>
#include <stdlib.h>

NODE* request_node(void);
LIST* request_list(void);
void release_node(NODE*);
void release_list(LIST*);

#endif /* LIST_ALLOC_H */
