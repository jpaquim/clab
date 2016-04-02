#include "matrix.h"

matrix matrix_zeros(size_t n_rows, size_t n_cols) {
    matrix mat = malloc(sizeof(*mat));
    mat->data  = malloc(n_rows*sizeof(*mat->data));
    *mat->data = calloc(n_rows*n_cols,sizeof(**mat->data));
    for(size_t i = 1; i < n_rows; ++i)
        mat->data[i] = mat->data[0]+i*n_cols;
    mat->n_rows = n_rows;
    mat->n_cols = n_cols;
    return mat;
}

matrix matrix_from_array(scalar *array, size_t n_rows, size_t n_cols) {
    matrix mat = matrix_zeros(n_rows,n_cols);
    memcpy(*mat->data,array,n_rows*n_cols*sizeof(scalar));
    return mat;
}

matrix copy_matrix(const matrix mat) {
    return matrix_from_array(*mat->data,mat->n_rows,mat->n_cols);
}

void delete_matrix(matrix mat) {
    free(*mat->data);
    free(mat->data);
    free(mat);
    return;
}

matrix matrix_from_vector(vector vec) {
    return matrix_from_array(vec->data,vec->n,1);
}

vector vector_from_matrix(matrix mat) {
    return vector_from_array(*mat->data,mat->n_rows*mat->n_cols);
}

matrix matrix_eye(size_t n) {
    matrix eye = matrix_zeros(n,n);
    for (size_t i = 0; i < n; ++i)
        eye->data[i][i] = 1.0;
    return eye;
}

matrix matrix_diag(vector vec) {
    matrix diag = matrix_zeros(vec->n,vec->n);
    for (size_t i = 0; i < vec->n; ++i)
        diag->data[i][i] = vec->data[i];
    return diag;
}

void print_matrix(const matrix mat) {
    putchar('\n');
    for (size_t i = 0; i < mat->n_rows; ++i) {
        for (size_t j = 0; j < mat->n_cols; ++j)
            printf("   % .4f", mat->data[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

void print_matrix_matlab(const matrix mat) {
    putchar('[');
    for (size_t i = 0; i < mat->n_rows; ++i) {
        if (i != 0)
            putchar(' ');
        for (size_t j = 0; j < mat->n_cols; ++j) {
            printf("% .4f", mat->data[i][j]);
            if (j != mat->n_cols-1)
                printf("  ");
        }
        if (i != mat->n_rows-1)
            printf(";\n");
    }
    printf("];\n");
}

vector matrix_row(const matrix mat, size_t row) {
    return vector_from_array(mat->data[row],mat->n_cols);
}

vector matrix_col(const matrix mat, size_t col) {
    vector vec_col = vector_zeros(mat->n_rows);
    for (size_t i = 0; i < mat->n_rows; ++i)
        vec_col->data[i] = mat->data[i][col];
    return vec_col;
}

matrix matrix_transpose(const matrix mat) {
    matrix transpose = matrix_zeros(mat->n_cols,mat->n_rows);
    for (size_t i = 0; i < mat->n_rows; ++i)
        for (size_t j = 0; j < mat->n_cols; ++j)
            transpose->data[j][i] = mat->data[i][j];
    return transpose;
}

matrix matrix_arrayfun(unary_function fun, const matrix A) {
    matrix B = matrix_zeros(A->n_rows,A->n_cols);
    for (size_t i = 0; i < A->n_rows; ++i)
        for (size_t j = 0; j < A->n_cols; ++j)
            B->data[i][j] = fun(A->data[i][j]);
    return B;
}

vector matrix_row_max(const matrix mat) {
    vector max = vector_zeros(mat->n_rows);
    for (size_t i = 0; i < mat->n_rows; ++i) {
        scalar max_row = -inf;
        for (size_t j = 0; j < mat->n_cols; ++j)
            if (mat->data[i][j] > max_row)
                max_row = mat->data[i][j];
        max->data[i] = max_row;
    }
    return max;
}

void check_matrix_sizes(const matrix A, const matrix B) {
    assert(A->n_rows == B->n_rows && A->n_cols == B->n_cols);
}

matrix matrix_bsxfun(binary_function f, const matrix A, const matrix B) {
    check_matrix_sizes(A,B);
    matrix C = matrix_zeros(A->n_rows,A->n_cols);
    for (size_t i = 0; i < A->n_rows; ++i)
        for (size_t j = 0; j < A->n_cols; ++j)
            C->data[i][j] = f(A->data[i][j],B->data[i][j]);
    return C;
}

// macro to simplify multiple matrix function definitions of the same kind
#define matrix_function_definition(op) \
matrix_function_prototype(op) {        \
    return matrix_bsxfun(op,A,B);      \
}

matrix_function_definition(plus)    // matrix_plus
matrix_function_definition(minus)   // matrix_minus
matrix_function_definition(times)   // matrix_times
matrix_function_definition(divide)  // matrix_divide
matrix_function_definition(idivide) // matrix_idivide
matrix_function_definition(mod)     // matrix_mod
matrix_function_definition(rem)     // matrix_rem
matrix_function_definition(power)   // matrix_power
matrix_function_definition(max)     // matrix_max
matrix_function_definition(min)     // matrix_min
matrix_function_definition(atan2)   // matrix_atan2
matrix_function_definition(atan2d)  // matrix_atan2d

matrix matrix_times_scalar(const matrix A, scalar b) {
    matrix C = matrix_zeros(A->n_rows,A->n_cols);
    for (size_t i = 0; i < A->n_rows; ++i)
        for (size_t j = 0; j < A->n_cols; ++j)
            C->data[i][j] = b*A->data[i][j];
    return C;
}

matrix matrix_mtimes(const matrix A, const matrix B) {
    assert(A->n_cols == B->n_rows);
    matrix C = matrix_zeros(A->n_rows,B->n_cols);
    for (size_t i = 0; i < A->n_rows; ++i)
        for (size_t k = 0; k < A->n_cols; ++k)
            for (size_t j = 0; j < B->n_cols; ++j)
                C->data[i][j] += A->data[i][k]*B->data[k][j];
    return C;
}

vector matrix_mtimes_vector(const matrix A, const vector b) {
    return vector_from_matrix(matrix_mtimes(A,matrix_from_vector(b)));
}
