#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int file_exists(char *file) {
  if(access(file, F_OK) == 0) {
    return 0;
  }

  return -1;
}

// Returns 0 if true, -1 otherwise.
int check_filetype(char *file1, char* file2) {
  char *ext1 = strrchr(file1, '.');
  char *ext2 = strrchr(file2, '.');

  if(ext1 != NULL && ext2 != NULL) {
    if(strcmp(ext1, ".txt") == 0 && strcmp(ext2, ".txt") == 0) {
      return 0;
    }
  }

  printf("Invalid file type, both files must be of type .txt\n");
  return -1; 
}

void get(char *local_file, char *remote_file) {
  if(file_exists(local_file) == 0) {
    printf("The file %s, already exists.", local_file);
    return;
  }
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

    // Because fgets reads in a newline when no input is given, we
    if(strcmp(input, "\n") != 0) {
      token = strtok(input, " ");
      input_args[arg_count] = token;

      while(token != NULL) {
        arg_count++;
        token = strtok(NULL, " ");
        input_args[arg_count] = token;
      }
    } else {
      input_args[0] = NULL;
    }

    // Strip the arguments of any newline characters.
    if(input_args != NULL) {
      for(int i = 0; i < arg_count; i++) {
        input_args[i] = strtok(input_args[i], "\n");
      }
    }

    if(arg_count == 1) {
      if(strcmp(input_args[0], "quit") == 0) {
        exit(EXIT_SUCCESS);
      }
    } else if(arg_count == 3) {
      if(strcmp(input_args[0], "get") == 0) {
        if(check_filetype(input_args[1], input_args[2]) == 0) {
          get(input_args[1], input_args[2]);
        } 
        return;
      } else if(strcmp(input_args[0], "put") == 0) {
        if(check_filetype(input_args[1], input_args[2]) == 0) {
          put(input_args[1], input_args[2]);
        } 
        return;
      }
    }
    
    // If the input arguments aren't valid the default behaviour is 
    // to reset the input to NULL and return an invalid message.
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