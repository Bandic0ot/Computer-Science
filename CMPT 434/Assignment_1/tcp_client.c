#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

void get(char *local_file, char *remote_file) {
  printf("GET: %s %s\n", local_file, remote_file);
}

void put(char *local_file, char *remote_file) {
  printf("PUT: %s %s\n", local_file, remote_file);
}

// Takes the given input and separates it by spaces, 
// each word becomes an element of the provided array.
void parse_input(char *input) {
    char *token;
    char *input_args[50];
    int arg_count = 0;

    token = strtok(input, " ");
    input_args[arg_count] = token;

    while(token != NULL) {
      arg_count++;
      token = strtok(NULL, " ");
      input_args[arg_count] = token;
    }

    if(arg_count == 1) {
      if(strcmp(input_args[0], "quit\n") == 0) {
        exit(0);
      }
    } else if(arg_count == 3) {
      if(strcmp(input_args[0], "get") == 0) {
        get(input_args[1], input_args[2]);
        return;
      } else if(strcmp(input_args[0], "put") == 0) {
        put(input_args[1], input_args[2]);
        return;
      }
    }
    
    // If the input arguments aren't valid the default behaviour is 
    // to reset the arguments to NULL and return an invalid message.
    input = NULL;

    printf("Invalid command.\n");
}

int main(int argc, char *argv[]) {
  int BUFFER = 100;
  // Validate the given command line argument.
  if(argc == 2) {
    printf("%s\n", argv[argc - 1]);
  } else {
    printf("Invalid command line arguments.\n");
    return 1;
  }

  // Program loop
  while(1) {
    char *input = malloc(sizeof(char) * BUFFER);

    printf("Please enter a command [get|put|quit] [local] [remote]:\n");
    fgets(input, BUFFER, stdin);

    parse_input(input);
  }

  return 0;
}