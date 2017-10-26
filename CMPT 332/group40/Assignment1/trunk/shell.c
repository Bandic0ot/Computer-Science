/* Sean Robson-Kullman */
/* skr519 */
/* 11182480 */
/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct parse_info {
	char **args;
	int inpipe;
	int outpipe;
	int background;
};

/* Returns an array full of parsed strings, as well as the number of strings */
/* in the array as the third argument. */
char **parse_args(char *string, int size, int *arg_count) {
	char **cmd_args;
	char *tokenized;
	int count;

	cmd_args = malloc(size * sizeof(char*));

	tokenized = strtok(string, " \r\t\v");
	count = 0;

	/* Turn the passed string into a series of tokens which we then */
	/* store in an array of strings to be returned by the function. */
	while(tokenized != NULL) {
		cmd_args[count] = tokenized;
		tokenized = strtok(NULL, " \r\t\v");
		count++;
	}

	*arg_count = count;

	return cmd_args;
}

int main(int argc, char *argv[]) {
	int i;
	int buffer_size;
	int arg_count;
	char *buffer;
	char **tokenized_args;

	buffer_size = 100;
	buffer = malloc(buffer_size * sizeof(char));

	/* Clear the screen to make it clear the shell has started */
	system("clear");
	
	while(1) { 
		/* Print a command prompt that also displays the current */
		/* working directory. */
		printf("%s$ ", getcwd(buffer, buffer_size));

		/* Get user input and parse it. */
		fgets(buffer, buffer_size, stdin);

		tokenized_args = parse_args(buffer, buffer_size, &arg_count);
		for(i = 0; i < arg_count; i++) {
			printf("%s\n", tokenized_args[i]);
		}



		if(tokenized_args[0][0]=='e'||tokenized_args[0][0]=='E'){
			if(tokenized_args[0][1]=='x'||tokenized_args[0][1]=='X'){
				if(tokenized_args[0][2]=='i'||tokenized_args[0][2]=='I'){
					if(tokenized_args[0][3]=='t'||tokenized_args[0][3]=='T'){
						return 0;
					}
				}
			}
                }else if(tokenized_args[0][0]=='c'){
			if('d'==tokenized_args[0][1]){
				if('.'==tokenized_args[1][0]){
					if('.'==tokenized_args[1][1]){
						/*prev directory*/
					}
				}
				
				if(1 == chdir(tokenized_args[1])){
					printf("successfully changed directories \n");
				}else{
					/* should implement an if statement to return to home if just "cd" */
					printf("did not change directories \n");
				}
			}

		}else if(tokenized_args[0][0]=='/'){

		}else {
                        printf("The request is not a valid command\n");
                }





	}

	return 0;
}
