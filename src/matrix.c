#include "matrix.h"

matrix m_empty(void) {
    matrix empty = {.ij = NULL, .m = 0, .n = 0};
    return empty;
}

matrix m_zeros(size_t m, size_t n) {
    matrix mat;
    mat.ij  = malloc(m * sizeof(*mat.ij));
    *mat.ij = calloc(m * n, sizeof(**mat.ij));
    for(size_t i = 1; i < m; ++i)
        mat.ij[i] = mat.ij[0]+i*n;
    mat.m = m;
    mat.n = n;
    return mat;
}

matrix m_ones(size_t m, size_t n) {
    matrix mat = m_zeros(m, n);
    for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < n; ++j)
            mat.ij[i][j] = 1.0;
    return mat;
}

matrix m_from_array(scalar *array, size_t m, size_t n) {
    matrix mat;
    bool copy = false; // true
    if (copy) {
        mat = m_zeros(m, n);
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

matrix m_copy(matrix mat) {
    matrix copy = m_zeros(mat.m, mat.n);
    memcpy(*copy.ij, *mat.ij, mat.m * mat.n * sizeof(scalar));
    return copy;
}

void m_delete(matrix *mat) {
    free(*mat->ij);
    free(mat->ij);
    *mat = m_empty();
}

matrix m_eye(size_t n) {
    matrix eye = m_zeros(n,n);
    for (size_t i = 0; i < n; ++i)
        eye.ij[i][i] = 1.0;
    return eye;
}

matrix m_diag(vector vec) {
    matrix diag = m_zeros(vec.n,vec.n);
    for (size_t i = 0; i < vec.n; ++i)
        diag.ij[i][i] = vec.i[i];
    return diag;
}
