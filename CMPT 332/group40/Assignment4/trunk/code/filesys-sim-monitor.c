/*
 * reader-writer-monitor.c
 *
 * Sean Robson-Kullman
 * 11182480
 * 
 *
 * Matthew Muulenga
 * 11144528
 * mam558
 *
 */

/*provided by Dwight Makaroff for A2*/

/*# Dwight Makaroff   */
/*# student number    */
/*# nsid              */
/*# November 7, 2008  */

/* No part of this program may be used for any profit or example for any
   purpose other than for help in A2 for CMPT 332 at the University
   of Saskatchewan in the fall term of 2011-12 without the expressed
   written consent of the author.

   *********** reader-writer.c ***********
*/


#include <stdio.h>
#include <standards.h>
#include <os.h>

#include "list.h"
#include "monitor.h"
#include "filesys-sim.h"

#define File0ReadOK 0
#define File0WriteOK 1
#define File1ReadOK 2
#define File1WriteOK 3
#define File2ReadOK 4
#define File2WriteOK 5
#define File3ReadOK 6
#define File3WriteOK 7
#define File4ReadOK 8
#define File4WriteOK 9
#define File5ReadOK 10
#define File5WriteOK 11
#define File6ReadOK 12
#define File6WriteOK 13
#define File7ReadOK 14
#define File7WriteOK 15
#define File8ReadOK 16
#define File8WriteOK 17
#define File9ReadOK 18
#define File9WriteOK 19
#define File10ReadOK 20
#define File10WriteOK 21
#define OKtoWrite 4
#define OKtoRead  3

int numReaders = 0;
int busy = 0;

/**** Note that this is mostly identical to the textbook solution ***/
/**** except for the added MonEnter and MonLeave calls            ***/


void StartRead()
{
  MonEnter();

  if (busy)
    {
      MonWait(OKtoRead);
    }
  numReaders++;
  printf("starting value of numReaders = %d\n", numReaders);

  MonSignal(OKtoRead);

  MonLeave();
}

void StopRead()
{
  MonEnter();

  numReaders--;
  printf("stopping value of numReaders = %d\n", numReaders);
  if (numReaders == 0) MonSignal(OKtoWrite);

  MonLeave();
}

void StartWrite()
{
  MonEnter();
  if ((numReaders !=0) || busy)
    MonWait(OKtoWrite);
  busy = 1;

  MonLeave();
}

void StopWrite()
{
  MonEnter();

  busy = 0;

  printf("about to signal reader %d\n", MyPid());

  MonSignal(OKtoRead);

  MonLeave();
}




void mkdir(struct inode curInode, char* name) {
  int i, x, w, y;
  struct dir* pac;
  struct inode* node;
  i = 0;
  x = 1;
  w = 0;
  y = 0;

  StartWrite();
  
  /* find free inode */
  for(i = 0; i < num_inode_blocks; i++){
    /* if the inode is empty */
    if(0 != check_inode_type(i)){ 
      memmove(node, diskblock[sblock->inode_start + y],sizeof(inodes));
      break;
    }
  }
  if(i == num_inode_blocks){
    return;
  }
  /* find out how many blocks needed */
  while (x*BLOCK_SIZE < sizeof(struct dir_entry)){ 
    x++;
  }
  /* find a large enough series of empty data blocks via bitmap*/
  while(w != x){
    w ++;
    if(check_bitmap(y) == 1){ /* 1 in the bitmap means that it is full */
      w = 0;
    }
    y ++;
  }
  /* set the data block reference in the bitmap to used */
  while(y > (y-x)){
    y --;
    set_bitmap_location(y,1);
  }
  /* take the memory in the free data blocks allocated for this file */
  memmove(pac, diskblock[sblock->freespace+y],x*BLOCK_SIZE);
  
  /*allocate inode for directory*/

  alloc_dir_entry(name, 0, i, pac);
  alloc_inode(sizeof(struct dir_entry), 0, 1, pac, node);
  for(w = 0; w < sizeof(curInode->address); w++){
    if (curInode->(*address[w]) == NULL){
      curInode->address[w] = node;
    }
  }

  StopWrite();
}




void rm(struct inode* curInode, int ref) {
  if(curInode->type == 0 || curInode->type == 1){
    return;
  }
  StartWrite();

  /*free inode, and realocate bitmap.*/

  StopWrite();
}



void rmdir(struct inode* curInode, int ref) {
  struct dir* pac;
  if(curInode->type == 0 || curInode->type == 2){
    return;
  }
  StartWrite();
  memmove(pac, curInode->address[ref], curInode->size);
  if(pac->number_of_files > 0){
    return;
  }
  /*free inode, and reset bitmap*/


  StopWrite();
}




void cd(struct inode* link) {
  struct dir* branch;
  if (link->type == 1){
    return;
  }
  StartRead();
  memmove(branch, dataBlock[link->address], link->size);


  StopRead();
}



void open(struct inode* link) {
  if (link->type == 0){
    return;
  }else if (link->type == 1){
    cd(link);
    return;
  }
  StartRead();
  MonEnter();
  
  if(busy) {
    MonWait(file);
  }

  check_bitmap(file);

  
}



void close() {
  /*close file*/
  StopRead();
}



void read() {

}

void write() {

}

void seek() {

}


