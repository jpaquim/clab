#include "matrix_l.h"
matrix_l ml_empty(void) {
    matrix_l empty = {.ij = NULL, .m = 0, .n = 0};
    return empty;
}

matrix_l ml_false(size_t m, size_t n) {
    matrix_l mat;
    mat.ij  = malloc(m * sizeof(*mat.ij));
    *mat.ij = calloc(m * n, sizeof(**mat.ij));
    for(size_t i = 1; i < m; ++i)
        mat.ij[i] = mat.ij[0] + i * n;
    mat.m = m;
    mat.n = n;
    return mat;
}

matrix_l ml_true(size_t m, size_t n) {
    matrix_l mat = ml_false(m, n);
    memset(*mat.ij, true, m * n * sizeof(scalar_l));
    return mat;
}

matrix_l ml_from_array(scalar_l *array, size_t m, size_t n) {
    matrix_l mat;
    bool copy = false;
    if (copy) {
        mat = ml_false(m, n);
        memcpy(*mat.ij, array, m * n * sizeof(scalar));
    } else {
        mat.ij  = malloc(m * sizeof(*mat.ij));
        *mat.ij = array;
        for(size_t i = 1; i < m; ++i)
            mat.ij[i] = mat.ij[0]+i*n;
        mat.m = m;
        mat.n = n;
    }
    return mat;
}

matrix_l ml_copy(matrix_l mat) {
    matrix_l copy = ml_false(mat.m, mat.n);
    memcpy(*copy.ij, *mat.ij, mat.m * mat.n * sizeof(scalar));
    return copy;
}

void ml_delete(matrix_l *mat) {
    free(*mat->ij);
    free(mat->ij);
    *mat = ml_empty();
}
