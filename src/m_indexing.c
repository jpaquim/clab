#include "matrix.h"

vector m_row(matrix mat, size_t row) {
    return v_from_array(mat.ij[row],mat.n);
}

vector m_col(matrix mat, size_t col) {
    vector vec_col = v_zeros(mat.m);
    for (size_t i = 0; i < mat.m; ++i)
        vec_col.i[i] = mat.ij[i][col];
    return vec_col;
}
