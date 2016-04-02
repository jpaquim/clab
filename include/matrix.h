#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h> // for malloc, calloc
#include <stdio.h>  // for printf
#include <string.h> // for memcpy
#include <assert.h>
#include "scalar.h"
#include "vector.h"

struct _matrix {
    scalar **data;
    size_t n_rows;
    size_t n_cols;
};
typedef struct _matrix* matrix;

// memory management

// returns matrix of size n_rows x n_cols initialized with zeros
matrix matrix_zeros(size_t n_rows,size_t n_cols);

// returns matrix of size n_rows x n_cols initialized with contents of array
matrix matrix_from_array(scalar *array, size_t n_rows, size_t n_cols);

// returns a copy of the matrix
matrix copy_matrix(const matrix mat);

// deletes the matrix from memory
void delete_matrix(matrix mat);



// type conversion

// returns a column matrix from a given vector
matrix matrix_from_vector(vector vec);

// returns a vector from a given matrix, flattens in row-major order if 2D
vector vector_from_matrix(matrix mat);



// special matrices

// returns identity matrix of size n x n
matrix matrix_eye(size_t n);

// returns diagonal matrix with the entries of vec
matrix matrix_diag(vector vec);



// unary operations

// prints the matrix's contents to stdin
void print_matrix(const matrix mat);

// prints the matrix's contents to stdin in matlab declaration format
void print_matrix_matlab(const matrix mat);

// returns a single row of the matrix as a vector
vector matrix_row(const matrix mat, size_t row);

// returns a single column of the matrix as a vector
vector matrix_col(const matrix mat, size_t col);

// returns the transpose of the matrix
matrix matrix_transpose(const matrix mat);

// returns the result of applying a function to every element of the matrix
matrix matrix_arrayfun(unary_function fun, const matrix A);



// row-wise operations

// returns vector with the row-wise maximum of matrix
vector matrix_row_max(const matrix mat);


// binary operations

// check if matrices are the same size
void check_matrix_sizes(const matrix A, const matrix B);

// applies a binary function to corresponding element pairs and returns result
matrix matrix_bsxfun(binary_function f, const matrix A, const matrix B);

// macro to simplify multiple matrix function declarations of the same kind
#define matrix_function_prototype(op)              \
matrix matrix_##op(const matrix A, const matrix B)

matrix_function_prototype(plus);    // matrix_plus
matrix_function_prototype(minus);   // matrix_minus
matrix_function_prototype(times);   // matrix_times
matrix_function_prototype(divide);  // matrix_divide
matrix_function_prototype(idivide); // matrix_idivide
matrix_function_prototype(mod);     // matrix_mod
matrix_function_prototype(rem);     // matrix_rem
matrix_function_prototype(power);   // matrix_power
matrix_function_prototype(max);     // matrix_max
matrix_function_prototype(min);     // matrix_min
matrix_function_prototype(atan2);   // matrix_atan2
matrix_function_prototype(atan2d);  // matrix_atan2d

// returns the product of a matrix with a scalar
matrix matrix_times_scalar(const matrix A, scalar scl);

// returns the matrix product of two matrices
matrix matrix_mtimes(const matrix A, const matrix B);

// returns the product of a matrix with a vector
vector matrix_mtimes_vector(const matrix A, const vector b);

#endif
