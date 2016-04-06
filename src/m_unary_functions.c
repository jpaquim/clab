#include "matrix.h"

matrix m_arrayfun(unary_function fun, matrix mat) {
    matrix B = m_zeros(mat.m,mat.n);
    for (size_t i = 0; i < mat.m; ++i)
        for (size_t j = 0; j < mat.n; ++j)
            B.ij[i][j] = fun(mat.ij[i][j]);
    return B;
}

#define m_elt_function_definition(op) \
m_elt_function_prototype(op) {        \
    return **m_##op##_opt(mat,0).ij;         \
}

#define m_col_function_definition(op) \
m_col_function_prototype(op) {        \
    return m_##op##_opt(mat,1);         \
}

#define m_row_function_definition(op) \
m_row_function_prototype(op) {        \
    return m_##op##_opt(mat,2);       \
}

#define m_unary_function_definitions(op) \
m_elt_function_definition(op)            \
m_col_function_definition(op)            \
m_row_function_definition(op)

m_unary_function_definitions(max)

matrix m_max_opt(matrix mat, size_t dim) {
    matrix out;
    switch (dim) {
        case 0: out = m_times_s(m_ones(1,1), -Inf); break;
        case 1: out = m_times_s(m_ones(1,mat.n), -Inf); break;
        case 2: out = m_times_s(m_ones(mat.m,1), -Inf); break;
    }
    for (size_t i = 0; i < mat.m; ++i)
        for (size_t j = 0; j < mat.n; ++j)
            switch (dim) {
                case 0:
                    if (mat.ij[i][j] > out.ij[0][0])
                        out.ij[0][0] = mat.ij[i][j];
                    break;
                case 1:
                    if (mat.ij[i][j] > out.ij[0][j])
                        out.ij[0][j] = mat.ij[i][j];
                    break;
                case 2:
                    if (mat.ij[i][j] > out.ij[i][0])
                        out.ij[i][0] = mat.ij[i][j];
                    break;
            }
    return out;
}

