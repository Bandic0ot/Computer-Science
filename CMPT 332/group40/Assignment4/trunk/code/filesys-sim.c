/*
 * Sean Robson-Kullman
 * 11182480
 * skr519
 *
 * Matthew Muulenga
 * 11144528
 * mam558
 *
 */

#include <stdio.h>
#include <standards.h>
#include <os.h>

#include "filesys-sim.h"
#include "monitor.h"

#define INTSIZE 1

struct superblock sblock;
int num_inode_blocks;
char *diskblock;

int check_bitmap(int file_size) {
  int size;
  int index; /* Starting location of freespace. */
  int i;

  /* Start the index at the start of the bitmap block. */
  index = sblock.bitmap_start * BLOCK_SIZE;
  size = 0;

  for(i = sblock.bitmap_start * BLOCK_SIZE; i < sblock.datablock_start * BLOCK_SIZE; i+=4) {
    if(diskblock[i] == 0) {
      size++;

      if(size >= file_size) {
        return index;
      }
    } else {
      index = i;
      size = 0;	    
    }
  } 

  return -1;
}

/*int 
check_bitmap(int i){
	return diskblock[(sblock.bitmap_start*BLOCK_SIZE/INTSIZE) + i];
}*/

void
set_bitmap_location(int location, int value){
	diskblock[(sblock.bitmap_start*BLOCK_SIZE/INTSIZE) + location] = value;
}

int 
check_inode_type(int i){
	struct inode* node;
	memmove(node, &diskblock[((sblock.inode_start*BLOCK_SIZE) + i*(sizeof(struct inode) +1))/INTSIZE], sizeof(struct inode));
	return node->type;
}

void
alloc_inode(int size, int nlinks, int type, void* address,struct inode* node){
	int i;
	node->size = size;
	node->number_of_links = nlinks;
	node->type = type;
	for (i = 0; i < sizeof(node->address); i++){
		node->address[i] = NULL;
	}
	node->address[0] = address;
}

void 
alloc_dir_entry(char* name, int numFiles, int numInode, struct dir_entry* temp){
	temp->name = name;
	temp->number_of_files = numFiles;
	temp->inode_num = numInode;
}

void filesys_init() {
}

int main() {
	int i;
	int *bitmap;
	int meta_blocks;

	struct inode *inode_array;

	diskblock = malloc((BLOCK_SIZE / 4) * NUMBER_OF_BLOCKS);
	inode_array = malloc(NUMBER_OF_INODES * sizeof(struct inode)); 
		
	/* 1 block for superblock, 4 blocks for inodes, 4 blocks for bitmap */
	meta_blocks = 1 + INODE_BLOCKS + BITMAP_BLOCKS;
	
	sblock.num_blocks = NUMBER_OF_BLOCKS;
	sblock.num_data_blocks = NUMBER_OF_BLOCKS - meta_blocks;
	sblock.num_inodes = NUMBER_OF_INODES;
	sblock.inode_start = 1;
	sblock.bitmap_start = 2 + INODE_BLOCKS;

	bitmap = malloc(sblock.num_data_blocks * sizeof(int));

	/* Move the super block into our virtual disk. */
	memmove((void *) diskblock, &sblock, sizeof(sblock));

	/* Move the inode blocks into our virtual disk. */
	memmove((void *) (diskblock + (BLOCK_SIZE / 4)), inode_array, NUMBER_OF_INODES * sizeof(struct inode));

	/* Move the bitmap into our virtual disk. */
	memmove((void *) (diskblock + sblock.bitmap_start * (BLOCK_SIZE / 4)), bitmap, sblock.num_data_blocks * sizeof(int));


	/* Testing file system layout */
	for(i = sblock.bitmap_start * (BLOCK_SIZE / 4); i < sblock.num_data_blocks * sizeof(int); i+=4) {
		diskblock[i] = 1;
	}
	for(i = 0; i < 5000; i++) {
		printf("Byte %d: %d\n", i, *(diskblock + i));
	}

	return 0;
}
