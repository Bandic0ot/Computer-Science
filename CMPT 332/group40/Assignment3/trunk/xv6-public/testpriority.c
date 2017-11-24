/*
 * # Sean Robson-Kullman
 * # skr519
 * # 11182480
 * # Matthew Mulenga
 * # mam558
 * # 11144528
 */

/* inspired by forktest.c */

#include "types.h"
#include "stat.h"
#include "user.h"

#define M 20

void
proctest(void)
{
	int n,pid;

	printf(1, "test priority scheduler.\n");
	
	for(n=0;n<M;n++){
		pid = fork();
		if(pid<0) break;
		if(pid == 0) exit();
	}

	if (n==M){
		printf(1,"fork called M times.\n",M);
		exit();
	}

	for(;n>0;n--){
		if(wait()<0){
			printf(1,"wait stopped early.\n");
			exit();
		}
	}

	if(wait() != -1){
		printf(1,"wait got too many.\n");
		exit();
	}

	printf(1,"proctest finished.\n");


}

int main(void)
{
	proctest();	
	exit();
}



