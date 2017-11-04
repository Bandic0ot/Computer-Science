/*
 * reader-writer-test.c
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

#include "monitor.h"
#include "reader-writer-monitor.h"
#include "reader-writer.c"
#include "list.h"




int main(){
	int conditional;
	printf("Hello, eh.\n");
	
	conditional = mainp();

	if(!conditional){
		printf("yes! \n");
	}else printf("no!\n");

	
	
	return 1;
}
