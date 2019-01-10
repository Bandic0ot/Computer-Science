#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

void get(char* local_file, char* remote_file) {
  printf("GET: %s %s\n", local_file, remote_file);
}

void put(char* local_file, char* remote_file) {
  printf("PUT: %s %s\n", local_file, remote_file);
}

int main(int argc, char *argv[]) {
  // Validate the given command line argument.
  if(argc == 2) {
    printf("%s\n", argv[argc - 1]);
  } else {
    printf("Invalid arguments.\n");
    return 1;
  }

  // Program loop
  while(1) {
    printf("Please enter a command [get|put|quit] [local] [remote]:\n");

    char command[5];
    char local_file[50];
    char remote_file[50];

    // Check to see if the right number of strings was given.
    if(scanf("%s %s %s", command, local_file, remote_file) <= 0) {
      printf("Invalid command.\n");
      continue;
    } else {
      // Match the user input to a known command.
      if(strcmp(command, "get") == 0) {
        get(local_file, remote_file);
      } else if(strcmp(command, "put") == 0) {
        put(local_file, remote_file);
      } else if(strcmp(command, "quit") == 0) {
        return 0;
      } else {
        printf("Invalid command.\n");
        continue;
      }
    }
  }

  return 0;
}