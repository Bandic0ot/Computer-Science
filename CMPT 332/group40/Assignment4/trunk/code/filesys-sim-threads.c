/*
 * reader-writer-monitor.c
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

#include <stdio.h>
#include <standards.h>
#include <os.h>

#include "filesys-sim.h"
#include "list.h"
#include "monitor.h"
#include "filesys-sim-monitor.c"


#define TIMESTHROUGH 0


int
random_number(){
	double i;
	i = rand() % 10;
	i = i/10;
	i = -1 * i;
	i = i*log(.6);
	return i;
}


void
random_function(struct inode* link){
	double i;
	i = random_number();
	i = i*9;
	if(i < 1){
		mkdir(link);
	}else if(i < 2){
		cd(link);
	}else if(i < 3){
		open(link);
		if(link->type == 1){
			close(link);
		}
	}else if(i < 4){
		close(link)
	}else if(i < 5){
		read(link);
	}else if (i < 6){
		write(link);
	}else if (i < 7){
		seek(link);
	}else if(i < 8){
		rm(link);
	}else {
		rmdir(link);
	}
	TIMESTHROUGH ++;
}






