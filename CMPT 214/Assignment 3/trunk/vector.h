// Matthew Mulenga
// mam558
// 11144528

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdint.h>

// An Elem is a (single precision) floating-point value either stored
// in a Vector, or else a (scalar) operand for a scalar operation on the
// Vector
typedef float Elem;

// A Vector consists of a dimension greater than zero and the elements of
//  the Vector
typedef struct {
    uint16_t size;
    Elem *array;
} Vector;

// The maximum 16 bit integer.
const int MAX_ELEMS = UINT16_MAX;

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
bool print_vec(Vector *v);

// alloc_vec
// Allocate an empty vector.
// Input:
//      - Nothing
// Output:
//      - A pointer to an empty vector.
//      - NULL if there is an error.
Vector *alloc_vec();

// dealloc_vec
// Deallocate a vector.
// Input:
//      - v != NULL
//      - v->size > 0
//      - v->array != NULL
// Output:
//      - Nothing
//      Effect: Deallocate all the memory used by v

void dealloc_vec(Vector *v);

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
Vector *extend_vec(Vector *v, Elem e);

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



#endif // _VECTOR_H_