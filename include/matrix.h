#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h> // for malloc, calloc
#include <stdio.h>  // for printf
#include <string.h> // for memcpy
#include <assert.h>
#include "scalar.h"
#include "vector.h"
#include "matrix_l.h"

typedef struct {
    scalar **ij;
    size_t m;
    size_t n;
} matrix; // numeric matrix


/************************************
 * Array Creation and Concatenation *
 ************************************/

/**
 * Creates an empty matrix
 * @return        empty matrix,
 */
matrix m_empty(void);

/**
 * Creates new zero matrix
 * @param  n_rows number of rows of the matrix
 * @param  n_cols number of columns of the matrix
 * @return        matrix of size n_rows x n_cols initialized with zeros
 */
matrix m_zeros(size_t n_rows, size_t n_cols);

/**
 * Creates new matrix filled with ones
 * @param  n_rows number of rows of the matrix
 * @param  n_cols number of columns of the matrix
 * @return        matrix of size n_rows x n_cols initialized with ones
 */
matrix m_ones(size_t m, size_t n);

/**
 * Creates matrix from the contents of an array
 * @param  array  source array, must be at least n_rows x n_cols in memory
 * @param  n_rows number of rows of the matrix
 * @param  n_cols number of columns of the matrix
 * @return        matrix of size n_rows x n_cols with the contents of the array
 */
matrix m_from_array(scalar *array, size_t n_rows, size_t n_cols);

/**
 * Copies matrix contents to another matrix
 * @param  mat original matrix
 * @return     matrix with same content as the original
 */
matrix m_copy(matrix mat);

/**
 * Deletes the matrix from memory, should be performed when it's not needed in
 * the following code.
 * @param mat matrix to be deleted
 */
void m_delete(matrix *mat);

/**
 * Identity matrix of dimension n
 * @param  n dimension of matrix
 * @return   identity matrix of size n x n
 */
matrix m_eye(size_t n);

/**
 * Diagonal matrix, entries of the main diagonal specified by the input vector
 * @param  vec vector of length n which contains the desired diagonal elements
 * @return     matrix of size n x n whose diagonal contains the elements of vec
 */
matrix m_diag(vector vec);


/************
 * Indexing *
 ************/

/**
 * Extracts a single row of the matrix, returns it as a vector
 * @param  mat input matrix
 * @param  row specified row
 * @return     vector containing the specified row of the input matrix
 */
vector m_row(matrix mat, size_t row);

/**
 * Extracts a single row of the matrix, returns it as a vector
 * @param  mat input matrix
 * @param  row specified row
 * @return     vector containing the specified row of the input matrix
 */
vector m_col(matrix mat, size_t col);


/********************
 * Array Dimensions *
 ********************/

scalar_l m_isempty(matrix mat);


/********************************
 * Sorting and Reshaping Arrays *
 ********************************/

/**
 * Calculates the matrix transpose
 * @param  mat input matrix
 * @return     matrix
 */
matrix m_transpose(matrix mat);

/**
 * Replicates matrix
 * @param  mat        input matrix
 * @param  n_rows_rep number of vertical repetitions
 * @param  n_cols_rep number of horizontal repetitions
 * @return            matrix that contains the replicated input matrix
 */
matrix m_repmat(matrix mat, size_t n_rows_rep, size_t n_cols_rep);


/*********************
 * Binary Operations *
 *********************/

/**
 * Asserts if the matrices are the same size,
 * @param A first input matrix
 * @param B second input matrix
 */
void m_check_sizes(matrix A, matrix B);

/**
 * Applies a binary function to corresponding element pairs in the input
 * matrices
 * @param  f binary function applied
 * @param  A first input matrix
 * @param  B second input matrix
 * @return   matrix that contains the result of the binary operation
 */
matrix m_bsxfun(binary_function f, matrix A, matrix B);

/**
 * Macro, when given a binary function op, generates a function prototype for
 * the elementwise function m_op(), useful for multiple function declarations
 * @param  op binary function name
 */
#define m_binary_function_prototype(op) \
matrix m_##op(matrix A, matrix B)

/**
 * Macro, when given a binary function op, generates a function definition for
 * the elementwise function m_op(), useful for multiple function definitions
 * @param  op binary function name
 */
#define m_binary_function_definition(op) \
    m_binary_function_prototype(op) {    \
    return m_bsxfun(op, A, B);           \
}

/**
 * matrix m_op(matrix A, matrix B), for op any elementwise
 * binary function, after being defined with the appropriate macro,
 * returns the result of applying the binary function op elementwise to the
 * corresponding matrix elements in A and B
 * @param  A first input matrix
 * @param  B second input matrix
 * @return   matrix that contains the result of applying the binary operation
 */
m_binary_function_prototype(plus);    // m_plus

m_binary_function_prototype(minus);   // m_minus

m_binary_function_prototype(times);   // m_times

m_binary_function_prototype(divide);  // m_divide

m_binary_function_prototype(idivide); // m_idivide

m_binary_function_prototype(mod);     // m_mod

m_binary_function_prototype(rem);     // m_rem

m_binary_function_prototype(power);   // m_power

m_binary_function_prototype(max);     // m_max

m_binary_function_prototype(min);     // m_min

m_binary_function_prototype(atan2);   // m_atan2

m_binary_function_prototype(atan2d);  // m_atan2d

/**
 * Multiplies two matrices, using the usual matrix product from linear algebra
 * @param  A first input matrix
 * @param  B second input matrix
 * @return   result of multiplying A with B, A * B
 */
matrix m_mtimes(matrix A, matrix B);

/**
 * Multiplies matrix with scalar
 * @param  A input matrix
 * @param  b input scalar
 * @return   matrix whose entries those of A, multiplied by b
 */
matrix m_times_s(matrix A, scalar b);

/**
 * Multiplies matrix with vector, using the usual matrix product from linear
 * algebra
 * @param  A input matrix
 * @param  b input vector
 * @return   result of multiplying A with b, A * b
 */
vector m_mtimes_v(matrix A, vector b);


/*************************
 * Relational Operations *
 *************************/

/**
 * Applies a binary function to corresponding element pairs in the input
 * matrices
 * @param  f binary function applied
 * @param  A first input matrix
 * @param  B second input matrix
 * @return   matrix that contains the result of the binary operation
 */
matrix_l ml_bsxfun_rel(relational_function f, matrix A, matrix B);

/**
 * Macro, when given a binary function op, generates a function prototype for
 * the elementwise function ml_op(), useful for multiple function declarations
 * @param  op binary function name
 */
#define ml_relational_function_prototype(op) \
matrix_l ml_##op(matrix A, matrix B)

/**
 * Macro, when given a binary function op, generates a function definition for
 * the elementwise function m_op(), useful for multiple function definitions
 * @param  op binary function name
 */
#define ml_relational_function_definition(op) \
ml_relational_function_prototype(op) {        \
    return ml_bsxfun_rel(op, A, B);           \
}

/**
 * matrix m_op(matrix A, matrix B), for op any elementwise
 * binary function, after being defined with the appropriate macro,
 * returns the result of applying the binary function op elementwise to the
 * corresponding matrix elements in A and B
 * @param  A first input matrix
 * @param  B second input matrix
 * @return   matrix that contains the result of applying the binary operation
 */
ml_relational_function_prototype(eq); // ml_eq

ml_relational_function_prototype(ne); // ml_ne

ml_relational_function_prototype(lt); // ml_lt

ml_relational_function_prototype(le); // ml_le

ml_relational_function_prototype(gt); // ml_gt

ml_relational_function_prototype(ge); // ml_ge

scalar_l m_isequal(matrix A, matrix B);
scalar_l ml_isequal(matrix_l A, matrix_l B);


/********************
 * Unary Operations *
 ********************/

/**
 * Applies a function to every element of the matrix
 * @param  fun unary function to be applied
 * @param  mat   input matrix
 * @return     matrix containing the result of the operation
 */
matrix m_arrayfun(unary_function fun, matrix A);


#define m_opt_function_prototype(op)       \
matrix m_##op##_opt(matrix mat, size_t dim)

#define m_elt_function_prototype(op) \
scalar m_##op##_elt(matrix mat)

#define m_col_function_prototype(op) \
matrix m_##op##_col(matrix mat)

#define m_row_function_prototype(op) \
matrix m_##op##_row(matrix mat)

#define m_unary_function_prototypes(op) \
m_opt_function_prototype(op);           \
m_elt_function_prototype(op);           \
m_col_function_prototype(op);           \
m_row_function_prototype(op)

m_unary_function_prototypes(max);


/******************
 * I/O operations *
 ******************/

/**
 * Prints the matrix's contents to stdout
 * @param mat input matrix
 */
void m_disp(matrix mat);

/**
 * Prints the matrix's name and contents to stdout
 * @param mat input matrix
 */
#define m_display(mat) do {   \
    putchar('\n');            \
    printf("%s =\n\n", #mat); \
    m_disp(mat);              \
} while (0)

/**
 * Prints the matrix's contents to stdin in matlab declaration format
 * @param mat input matrix
 */
void m_print_matlab(matrix mat);


/*******************
 * Type Conversion *
 *******************/

/**
 * Converts a vector to an equivalent column matrix
 * @param  vec vector of length n
 * @return     matrix of size n x 1 with the the vector's contents
 */
matrix m_from_v(vector vec);

/**
 * Converts a matrix to an equivalent vector, flattening by rows if the matrix
 * is not a column/row.
 * @param  mat matrix of size n_rows x n_cols
 * @return     vector of length n_rows * n_cols
 */
vector v_from_m(matrix mat);

scalar s_from_m(matrix mat);

scalar_l l_from_m(matrix mat);

#endif
