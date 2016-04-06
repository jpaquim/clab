#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h> // for malloc, calloc
#include <stdio.h>  // for printf
#include <string.h> // for memcpy
#include "scalar.h"

typedef struct {
    scalar *i;
    size_t n;
} vector;

// memory management

// returns vector of length n initialized with zeros
vector v_zeros(size_t n);

// returns vector of size n initialized with contents of array
vector v_from_array(scalar *array, size_t n);

// returns a copy of the vector
vector v_copy(vector vec);

// deletes the vector from memory
void v_delete(vector vec);



// unary operations

// prints the vector's contents to stdin
void v_print(vector vec);

// returns the maximum element of the vector
scalar v_max_elem(vector vec);

// computes the sum of all elements in the vector
scalar v_sum_elem(vector vec);



// binary operations

// check if vectors are the same length
void v_check_sizes(vector a, vector b);

// applies a binary function to corresponding element pairs and returns result
vector v_bsxfun(binary_function f, vector a, vector b);

// macro to simplify multiple vector function declarations of the same kind
#define v_function_prototype(op)              \
vector v_##op(vector a, vector b)

v_function_prototype(plus);    // v_plus
v_function_prototype(minus);   // v_minus
v_function_prototype(times);   // v_times
v_function_prototype(divide);  // v_divide
v_function_prototype(idivide); // v_idivide
v_function_prototype(mod);     // v_mod
v_function_prototype(rem);     // v_rem
v_function_prototype(power);   // v_power
v_function_prototype(max);     // v_max
v_function_prototype(min);     // v_min
v_function_prototype(atan2);   // v_atan2
v_function_prototype(atan2d);  // v_atan2d

// returns the product of a vector with a scalar
vector v_times_scalar(vector a, scalar b);

// returns the dot product of two vectors
scalar v_dot(vector a, vector b);

#endif
