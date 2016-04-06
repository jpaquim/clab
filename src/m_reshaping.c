#include "matrix.h"

matrix m_transpose(matrix mat) {
    matrix transpose = m_zeros(mat.n,mat.m);
    for (size_t i = 0; i < mat.m; ++i)
        for (size_t j = 0; j < mat.n; ++j)
            transpose.ij[j][i] = mat.ij[i][j];
    return transpose;
}

matrix m_repmat(matrix mat, size_t m_rep, size_t n_rep) {
    matrix rep = m_zeros(m_rep*mat.m, n_rep*mat.n);
    for (size_t i = 0; i < mat.m; ++i)
        for (size_t k = 0; k < m_rep; ++k)
            for (size_t l = 0; l < n_rep; ++l)
                for (size_t j = 0; j < mat.n; ++j)
                    rep.ij[i+k*mat.m][j+l*mat.n] =
                        mat.ij[i][j];
    return rep;
}
