// Matthew Mulenga
// mam558
// 11144528

// -------- Headers --------

#include <assert.h>	// For assert()
#include <stdio.h>	// For printf()
#include <inttypes.h>	// For uint16_t and UINT16_MAX
#include <stdint.h>
#include <stdlib.h> // For EXIT_SUCCESS

#include "vector.h" // For Vector, Elem, and MAX_ELEMS

// -------- Methods --------

// print_vec
// Displays the vector.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
// Output:
//      - True, if the vector was successfully displayed.
//      - False, otherwise.
//      Effect: Vector elements are all displayed on console.
bool print_vec(Vector *v) {
    if (NULL != v) {
        for (uint16_t i = 0; i < v->size; i++) {
            printf("%f\n", v->array[i]);
        }
        printf("\n");
        
        return true;
    }
    
    return false;
}

// alloc_vec
// Allocate an empty vector.
// Input:
//      - Nothing
// Output:
//      - A pointer to an empty vector.
//      - NULL if there is an error.
Vector *alloc_vec() {
    // Initialize a new Vector structure.
    Vector *emptyVector = new Vector;
    // If for some reason the array is null, release the allocated memory.
    if (NULL == emptyVector) {
        delete emptyVector;
        return NULL;
    }
    
    emptyVector->size = 0;
    
    // Allocate space for an empty array of type Element
    emptyVector->array = new Elem[emptyVector->size];
    // If for some reason the array is null, release the allocated memory.
    // Otherwise return the emptyVector pointer.
    if (NULL == emptyVector->array) {
        delete emptyVector->array;
        return NULL;
    } else {
        return emptyVector;
    }
    
    return NULL;
}

// dealloc_vec
// Deallocate a vector.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
// Output:
//      - Nothing
//      Effect: Deallocate all the memory used by v

void dealloc_vec(Vector *v) {
    if(v->size > 0) {
    	delete[] v->array;
    	delete v;
    }
}

// extend_vec
// Allocates a new vector one element greater in size than
// the input vector and copies the elements into the new vector.
// The new element is added to the end of the new vector.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
//      - e is an float
// Output:
//      - A pointer to the new vector.
//      - NULL if there is an error.
Vector *extend_vec(Vector *v, Elem e) {
	// Check to see if we have reached the integer size limit.
	if(v->size >= MAX_ELEMS) {
		return NULL;
	}
	
    Vector *extVector = new Vector;
    
    // Check to see if the new vector was allocated properly
    // if not delete it and return NULL.
    if (NULL == extVector) {
        delete extVector;
        return NULL;
    } else {
    // Otherwise we set the new vectors size and number of elements.
        extVector->size = v->size + 1;
        extVector->array = new Elem[extVector->size];
    }
    
    // Populate the new array with the values from the old array.
    for (uint16_t i = 0; i < v->size; i++) {
        extVector->array[i] = v->array[i];
    }
    
    // Set the last element in the array to e.
    extVector->array[v->size] = e;
    
    return extVector;
}


