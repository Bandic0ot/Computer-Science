// Matthew Mulenga
// mam558
// 11144528

#ifndef _SCALAR_H_
#define _SCALAR_H_

// -------- Headers --------

#include "vector.h" // For Vector

Vector *scalar_plus(Vector *v, Elem e);

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
Vector *scalar_minus(Vector *v, Elem e);

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
Vector *scalar_mult(Vector *v, Elem e);

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
Vector *scalar_div(Vector *v, Elem e);


#endif // _SCALAR_H_