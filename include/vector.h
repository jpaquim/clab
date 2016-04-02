#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h> // for malloc, calloc
#include <stdio.h>  // for printf
#include <string.h> // for memcpy
#include "scalar.h"

struct _vector {
    scalar *data;
    size_t n;
};
typedef struct _vector* vector;

// memory management

// returns vector of length n initialized with zeros
vector vector_zeros(size_t n);

// returns vector of size n initialized with contents of array
vector vector_from_array(const scalar *array, size_t n);

// returns a copy of the vector
vector copy_vector(const vector vec);

// deletes the vector from memory
void delete_vector(vector vec);



// unary operations

// prints the vector's contents to stdin
void print_vector(const vector vec);

// returns the maximum element of the vector
scalar vector_max_elem(const vector vec);

// computes the sum of all elements in the vector
scalar vector_sum_elem(const vector vec);



// binary operations

// check if vectors are the same length
void check_vector_sizes(const vector a, const vector b);

// applies a binary function to corresponding element pairs and returns result
vector vector_bsxfun(binary_function f, const vector a, const vector b);

// macro to simplify multiple vector function declarations of the same kind
#define vector_function_prototype(op)              \
vector vector_##op(const vector a, const vector b)

vector_function_prototype(plus);    // vector_plus
vector_function_prototype(minus);   // vector_minus
vector_function_prototype(times);   // vector_times
vector_function_prototype(divide);  // vector_divide
vector_function_prototype(idivide); // vector_idivide
vector_function_prototype(mod);     // vector_mod
vector_function_prototype(rem);     // vector_rem
vector_function_prototype(power);   // vector_power
vector_function_prototype(max);     // vector_max
vector_function_prototype(min);     // vector_min
vector_function_prototype(atan2);   // vector_atan2
vector_function_prototype(atan2d);  // vector_atan2d

// returns the product of a vector with a scalar
vector vector_times_scalar(const vector a, scalar b);

// returns the dot product of two vectors
scalar vector_dot(const vector a, const vector b);

#endif
