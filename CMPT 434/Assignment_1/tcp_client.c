#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

void get() {
  printf("This is a get function.\n");
}

void put() {
  printf("This is the put function.\n");
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
    printf("Please enter a command [get] [put] [quit]:\n");

    char command[5];
    scanf("%s", command);

    // Match the user input to a known command.
    if(strcmp(command, "get") == 0) {
      get();
    } else if(strcmp(command, "put") == 0) {
      put();
    } else if(strcmp(command, "quit") == 0) {
      break;
    } else {
      printf("Invalid command.\n");
      continue;
    }
  }

  return 0;
}