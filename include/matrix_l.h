#ifndef MATRIX_L_H
#define MATRIX_L_H

#include <stdlib.h> // for malloc, calloc
#include <stdio.h>  // for printf
#include <string.h> // for memcpy
#include <assert.h>
#include "scalar.h"

typedef struct {
    scalar_l **ij;
    size_t m;
    size_t n;
} matrix_l; // logical matrix


/************************************
 * Array Creation and Concatenation *
 ************************************/

/**
 * Creates an empty matrix
 * @return        empty matrix,
 */
matrix_l ml_empty(void);

/**
 * Creates new zero matrix
 * @param  n_rows number of rows of the matrix
 * @param  n_cols number of columns of the matrix
 * @return        matrix of size n_rows x n_cols initialized with zeros
 */
matrix_l ml_false(size_t n_rows, size_t n_cols);

/**
 * Creates new matrix filled with ones
 * @param  n_rows number of rows of the matrix
 * @param  n_cols number of columns of the matrix
 * @return        matrix of size n_rows x n_cols initialized with ones
 */
matrix_l ml_true(size_t m, size_t n);

/**
 * Creates matrix from the contents of an array
 * @param  array  source array, must be at least n_rows x n_cols in memory
 * @param  n_rows number of rows of the matrix
 * @param  n_cols number of columns of the matrix
 * @return        matrix of size n_rows x n_cols with the contents of the array
 */
matrix_l ml_from_array(scalar_l *array, size_t n_rows, size_t n_cols);

/**
 * Copies matrix contents to another matrix
 * @param  mat original matrix
 * @return     matrix with same content as the original
 */
matrix_l ml_copy(matrix_l mat);

/**
 * Deletes the matrix from memory, should be performed when it's not needed in
 * the following code.
 * @param mat matrix to be deleted
 */
void ml_delete(matrix_l *mat);


void ml_check_sizes(matrix_l A, matrix_l B);

matrix_l ml_bsxfun(binary_function_l f, matrix_l A, matrix_l B);

/**
 * Macro, when given a binary function op, generates a function prototype for
 * the elementwise function m_op(), useful for multiple function declarations
 * @param  op binary function name
 */
#define ml_logical_function_prototype(op) \
matrix_l ml_##op(matrix_l A, matrix_l B)

/**
 * Macro, when given a logical function op, generates a function definition for
 * the elementwise function m_op(), useful for multiple function definitions
 * @param  op logical function name
 */
#define ml_logical_function_definition(op) \
ml_logical_function_prototype(op) {       \
    return ml_bsxfun(op, A, B);           \
}

/**
 * matrix_l ml_op(matrix_l A, matrix_l B), for op any elementwise
 * binary function, after being defined with the appropriate macro,
 * returns the result of applying the binary function op elementwise to the
 * corresponding matrix elements in A and B
 * @param  A first input matrix
 * @param  B second input matrix
 * @return   matrix that contains the result of applying the binary operation
 */
ml_logical_function_prototype(and); // m_and

ml_logical_function_prototype(or);  // m_or

ml_logical_function_prototype(xor); // m_xor


matrix_l ml_arrayfun(unary_function_l fun, matrix_l mat);

#define ml_opt_function_prototype(op)            \
matrix_l ml_##op##_opt(matrix_l mat, size_t dim)

#define ml_elt_function_prototype(op) \
scalar_l ml_##op##_elt(matrix_l mat)

#define ml_col_function_prototype(op) \
matrix_l ml_##op##_col(matrix_l mat)

#define ml_row_function_prototype(op) \
matrix_l ml_##op##_row(matrix_l mat)

#define ml_unary_function_prototypes(op) \
ml_opt_function_prototype(op);           \
ml_elt_function_prototype(op);           \
ml_col_function_prototype(op);           \
ml_row_function_prototype(op)

ml_unary_function_prototypes(all);
ml_unary_function_prototypes(any);

scalar_l l_from_ml(matrix_l mat);


/******************
 * I/O operations *
 ******************/

/**
 * Prints the matrix's contents to stdout
 * @param mat input matrix
 */
void ml_disp(matrix_l mat);

/**
 * Prints the matrix's name and contents to stdout
 * @param mat input matrix
 */
#define ml_display(mat) do {   \
    putchar('\n');             \
    printf("%s =\n\n", #mat);  \
    ml_disp(mat);              \
} while (0)

/**
 * Prints the matrix's contents to stdin in matlab declaration format
 * @param mat input matrix
 */
void ml_print_matlab(matrix_l mat);


#endif
