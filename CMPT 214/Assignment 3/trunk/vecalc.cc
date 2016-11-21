// Matthew Mulenga
// 11144528
// mam558


#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef float Element;
typedef struct {
    uint16_t size;
    Element *array;
} Vector;

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
    emptyVector->array = new Element[emptyVector->size];
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
    delete v;
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
Vector *extend_vec(Vector *v, Element e) {
    Vector *extVector = new Vector;
    
    if (NULL == extVector) {
        delete extVector;
        return NULL;
    } else {
        extVector->size = v->size + 1;
        extVector->array = new Element[extVector->size];
    }
    
    for (uint16_t i = 0; i < v->size; i++) {
        extVector->array[i] = v->array[i];
    }
    
    extVector->array[v->size] = e;
    
    return extVector;
}

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
Vector *scalar_plus(Vector *v, Element e) {
    
    for (uint16_t i = 0; i < v->size; i++) {
        v->array[i] += e;
    }
    
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
Vector *scalar_minus(Vector *v, Element e) {
    
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
Vector *scalar_mult(Vector *v, Element e) {

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
Vector *scalar_div(Vector *v, Element e) {

    return NULL;
}

// Usage
//  Instruct user on how to use this program; i.e. the commands it
//  supports and the syntax of those commands.
// In:
//    none
// Out:
//    output produced on standard output
void usage( void ) {
    puts( " Usage:" );
    puts( "  p   - print vector" );
    puts( "  q,e - quit, end" );
    puts( "  h   - print usage help" );
    puts( "  + <operand> - add <operand> to each element of vector" );
    puts( "  - <operand> - subtract <operand> from each element of vector" );
    puts( "  * <operand> - multiple each element of vector by <operand>" );
    puts( "  / <operand> - divide each element of vector by <operand>" );
    puts( "  a <value> - extend vector by additional value" );
}

int main(int, char **) {
    
#ifdef TESTING
    const float TEST_FLOAT_1 = 5.25;
    const float TEST_FLOAT_2 = 8.75;
    const float TEST_FLOAT_3 = 6.25;
    const float TEST_FLOAT_4 = 11.00;
    
    // Test alloc_vec() method
    Vector *v1 = alloc_vec();
    
    assert(NULL != v1);
    assert(0 == v1->size);
    assert(NULL != v1->array);
    
    // Test extend_vec() method
    Vector *v2 = extend_vec(v1, TEST_FLOAT_1);
    Vector *v3 = extend_vec(v2, TEST_FLOAT_2);
    
    assert(NULL != v2);
    assert(1 == v2->size);
    assert(NULL != v2->array);
    
    assert(NULL != v3);
    assert(2 == v3->size);
    assert(NULL != v3->array);
    
    assert(TEST_FLOAT_1 == v2->array[0]);
    assert(TEST_FLOAT_2 == v3->array[1]);
    
    // Test print_vec() method
    // Expected:
    /*
    
    5.250000
    
    5.250000
    8.750000
    */
    print_vec(v1);
    print_vec(v2);
    print_vec(v3);
    
    // Test scalar_plus() method
    Vector *v2plus = scalar_plus(v2, 1.0);
    Vector *v3plus = scalar_plus(v3, 2.25);
    
    assert(NULL != v2plus);
    assert(1 == v2plus->size);
    assert(NULL != v2plus->array);
    
    assert(NULL != v3plus);
    assert(2 == v3plus->size);
    assert(NULL != v3plus->array);
    
    assert(TEST_FLOAT_3 == v2plus->array[0]);
    assert(TEST_FLOAT_4 == v3plus->array[1]);

    //Test scalar_minus() method
    assert(NULL != scalar_minus(v1, 1.0));
    
    //Test scalar_mult() method
    assert(NULL != scalar_mult(v1, 2.0));

    //Test scalar_div() method
    assert(NULL != scalar_div(v1, 2.0));

    // Test dealloc_vec() method
    dealloc_vec(v1);
    dealloc_vec(v2);
    dealloc_vec(v3);
    
#endif // TESTING
    
    return 0;
}
