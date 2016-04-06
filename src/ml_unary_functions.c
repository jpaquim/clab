#include "matrix_l.h"

matrix_l ml_arrayfun(unary_function_l fun, matrix_l mat) {
    matrix_l B = ml_false(mat.m, mat.n);
    for (size_t i = 0; i < mat.m; ++i)
        for (size_t j = 0; j < mat.n; ++j)
            B.ij[i][j] = fun(mat.ij[i][j]);
    return B;
}

#define ml_elt_function_definition(op)      \
ml_elt_function_prototype(op) {             \
    return l_from_ml(ml_##op##_opt(mat, 0)); \
}

#define ml_col_function_definition(op) \
ml_col_function_prototype(op) {        \
    return ml_##op##_opt(mat, 1);      \
}

#define ml_row_function_definition(op) \
ml_row_function_prototype(op) {        \
    return ml_##op##_opt(mat, 2);      \
}

#define ml_unary_function_definitions(op) \
ml_elt_function_definition(op)            \
ml_col_function_definition(op)            \
ml_row_function_definition(op)

ml_unary_function_definitions(all)
ml_unary_function_definitions(any)

matrix_l ml_all_opt(matrix_l mat, size_t dim) {
    matrix_l out;
    switch (dim) {
        case 0: out = ml_true(1,1); break;
        case 1: out = ml_true(1,mat.n); break;
        case 2: out = ml_true(mat.m,1); break;
    }
    for (size_t i = 0; i < mat.m; ++i)
        for (size_t j = 0; j < mat.n; ++j)
            switch (dim) {
                case 0: out.ij[0][0] = out.ij[0][0] && mat.ij[i][j]; break;
                case 1: out.ij[0][j] = out.ij[0][j] && mat.ij[i][j]; break;
                case 2: out.ij[i][0] = out.ij[i][0] && mat.ij[i][j]; break;
            }
    return out;
}

matrix_l ml_any_opt(matrix_l mat, size_t dim) {
    matrix_l out;
    switch (dim) {
        case 0: out = ml_false(1,1); break;
        case 1: out = ml_false(1,mat.n); break;
        case 2: out = ml_false(mat.m,1); break;
    }
    for (size_t i = 0; i < mat.m; ++i)
        for (size_t j = 0; j < mat.n; ++j)
            switch (dim) {
                case 0: out.ij[0][0] = out.ij[0][0] || mat.ij[i][j]; break;
                case 1: out.ij[0][j] = out.ij[0][j] || mat.ij[i][j]; break;
                case 2: out.ij[i][0] = out.ij[i][0] || mat.ij[i][j]; break;
            }
    return out;
}
