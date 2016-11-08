#include <stdio.h>
#include <string.h>

int o;
int npvle;

int main( int argc, char* argv[]) {
    char *copyp;		// space for floating-point value

    // check that we have enough arguments
    if ( argc < 3 )
    {   fprintf( stderr, "Not enough arguments.\n" );
	// return -1
	return -1; }
      
    // set the operation code depending on the first argument  
    if( 0==strcmp( argv[1], "add" ) )	{
	o = 5;
    }
    else if (0 == strcmp( argv[1], "multiply")) 
    {	o = 7; 
    } else {
	fprintf( stderr, "operation not recognized!\n" );
	return -1; }
	
    // copy second argument into dynamically allocated
    // string 
    copyp = new char[strlen(argv[2])];
    strcpy( copyp, argv[2] );

    // get the input value
    sscanf( copyp, "%d", &npvle );

    return 0;
}

