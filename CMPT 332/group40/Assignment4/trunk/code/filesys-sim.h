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

#define BLOCK_SIZE 512
#define NUMBER_OF_BLOCKS 500
#define NUMBER_OF_INODES 100
#define INODE_BLOCKS 4
#define BITMAP_BLOCKS 4
#define META_BLOCKS 9
#define MAX_FILES 10
#define MAX_BLOCKS 10 /* Maximum number of blocks an operation can use. */
#define DIRSIZE 5
#define ROOT 1

struct superblock {
	int num_blocks; /* Number of blocks. */
	int num_data_blocks; /* Number of data blocks. */
	int num_inodes; /* Number of inodes. */
	int inode_start; /* Block number of first inode. */
	int bitmap_start; /* Block number of first bitmap entry. */
	int datablock_start; /* Block number of first datablock entry. */
	struct dir_entry *root; /* Pointer to root directory. */
};

struct inode {	
	int size; /* Size of the file in bytes. */
	int number_of_links;
	int type; /* 0 = empty, 1 = dir, 2 = file */
	void *address[DIRSIZE];
};

struct dir_entry {
	char *name;
	int number_of_files;
	int inode_num;
};
