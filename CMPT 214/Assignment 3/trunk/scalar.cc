// Matthew Mulenga
// mam558
// 11144528

// -------- Headers --------

#include <inttypes.h> // For uint16
#include <stdlib.h> // For NULL
//#include <stdint.h>	// For uint16_t, UINT16_MAX on Linux

#include "scalar.h" // For definitions specific to this module.
#include "vector.h" // For Vector

// -------- Methods --------

// scalar_plus
// Adds a given scalar to each element of the vector.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
//      - e is a float
// Output:
//      - A pointer to the modified vector.
//      - NULL if there is an error.
Vector *scalar_plus(Vector *v, Elem e) {
    
    // Add e to each element of the vector.
    for (uint16_t i = 0; i < v->size; i++) {
        v->array[i] += e;
    }
    
    // Make sure the addition worked properly.
    if (NULL != v) {
        return v;
    }
    
    return NULL;
}

// scalar_minus
// Subtracts a given scalar from each element of the vector.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
//      - e is a float
// Output:
//      - A pointer to the modified vector.
//      - NULL if there is an error.
Vector *scalar_minus(Vector *v, Elem e) {

	// Subtract e from each element of the vector.
	for (uint16_t i = 0; i < v->size; i++) {
        v->array[i] -= e;
    }
    
    // Make sure the subtraction worked properly.
    if (NULL != v) {
        return v;
    }
    
    return NULL;
}

// scalar_mult
// Multiplies each element of the vector by a given scalar.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
//      - e is a float
// Output:
//      - A pointer to the modified vector.
//      - NULL if there is an error.
Vector *scalar_mult(Vector *v, Elem e) {

	// Multiply each element of the vector by e.
	for (uint16_t i = 0; i < v->size; i++) {
        v->array[i] *= e;
    }
    
    // Make sure the multiplication worked.
    if (NULL != v) {
        return v;
    }

    return NULL;
}

// scalar_div
// Divides each element of the vector by a given scalar.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
//      - e is a float
//      - e != 0
// Output:
//      - A pointer to the modified vector.
//      - NULL if there is an error.
Vector *scalar_div(Vector *v, Elem e) {

	// Divide each element of the vector by e.
	for (uint16_t i = 0; i < v->size; i++) {
        v->array[i] /= e;
    }
    
    // Make sure the division worked.
    if (NULL != v) {
        return v;
    }

    return NULL;
}