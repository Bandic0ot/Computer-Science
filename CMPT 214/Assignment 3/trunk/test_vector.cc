// Matthew Mulenga
// mam558
// 11144528

#include <assert.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

Vector *v, *v1, *v2, *v3, *v4, *v5;
bool TEST_BOOL;

// Unit test for test_alloc() method.
void test_alloc() {
	Vector *v = alloc_vec();
	
	assert(NULL != v); // Make sure the vector was allocated properly.
	assert(0 == v->size); // Make sure the vector has the proper size.
	assert(0 == v->array[0]); // Make sure there is nothing in the array.
	
	dealloc_vec(v); // Release the memory used by the vector.
}

// Unit test for extend_vec() method.
void test_extend() {
	
	v = alloc_vec();
	
	assert(NULL != v); // Make sure the vector was allocated properly.
	assert(0 == v->size); // Make sure the vector has the proper size.
	assert(0 == v->array[0]); // Make sure there is nothing in the array.
	
	// Test the extend_vec() method.
	v1 = extend_vec(v, 5.00);
	
	assert(NULL != v1); // Check to see if the extension worked.
	assert(1 == v1->size); // Make sure the size of the array has increased.
	assert(5.00 == v1->array[0]); // Make sure that the correct value was
								  // stored in the correct location.
	
	// Test the extend_vec() method using MAXFLOAT
	v2 = extend_vec(v1, MAXFLOAT); 
	assert(NULL != v2); // Check to see if the extension worked.
	assert(2 == v2->size); // Make sure the size of the array has increased.
	assert(MAXFLOAT == v2->array[1]); // Make sure that the correct value was
								  	  // stored in the correct location.
	
	// Test the extend_vec() method by overloading with MAX_ELEMS
	v3 = new Vector;
	v3->array = new Elem[MAX_ELEMS - 1];
	v3->size = MAX_ELEMS - 1;
	v4 = extend_vec(v3, 8.00);
	assert(NULL != v4); // Check to see if the extension worked.
	assert(MAX_ELEMS == v4->size); // Make sure the size of the array has increased.
	assert(8.00 == v4->array[MAX_ELEMS - 1]); // Make sure that the correct value was
								  			  // stored in the correct location.
	
	v5 = extend_vec(v4, 5.00);
	assert(NULL == v5); // Check to see if the vector failed to increase which it
						// should.
						
	/* Release the memory used by all the vectors.
	dealloc_vec(v1);
	dealloc_vec(v2);
	dealloc_vec(v3);
	dealloc_vec(v4);
	dealloc_vec(v5);*/
	
}

// Unit test for print_vec() method
void test_print() {
	
	// Check to see if the correct output is being printed.
	// Expected outputs: 5.00, 5.00 MAXFLOAT, nothing
	assert(true == print_vec(v1));
	assert(true == print_vec(v2));
	assert(false == print_vec(v5)); // Should get nothing because v5 is NULL
	
}

int main(int, char **) {
    
    test_alloc();
    test_extend();
    test_print();

    return EXIT_SUCCESS;
}