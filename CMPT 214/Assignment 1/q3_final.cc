#include <stdio.h>
#include <string.h>

int operationCode;
int inputValue;

int main( int argc, char* argv[]) {
	// Allocate space for a pointer to a character.
	char *copyChar;

 	// Check that we have enough arguments.
   	if (argc < 3) {

		fprintf( stderr, "Not enough arguments.\n" );

		return -1;
	}
      
	// Set the operation code depending on the first argument.  
	if (0 == strcmp(argv[1], "add")) {

		operationCode = 5;

	} else if (0 == strcmp(argv[1], "multiply")) {

		operationCode = 7; 

	} else {

		fprintf( stderr, "operation not recognized!\n" );

		return -1;
	}
	
	// Dynamically allocate a new string and then copy the
	// second agrument of main into the new string.
	copyp = new char[strlen(argv[2])];
	strcpy(copyChar, argv[2]);

	// Get the value stored in copyp and store it in inputValue
	sscanf(copyChar, "%d", &inputValue);

    return 0;
}

