#include "matrix_l.h"

void ml_check_sizes(matrix_l A, matrix_l B) {
    assert(A.m == B.m && A.n == B.n);
}

matrix_l ml_bsxfun(binary_function_l f, matrix_l A, matrix_l B) {
    ml_check_sizes(A,B);
    matrix_l C = ml_false(A.m, A.n);
    for (size_t i = 0; i < A.m; ++i)
        for (size_t j = 0; j < A.n; ++j)
            C.ij[i][j] = f(A.ij[i][j], B.ij[i][j]);
    return C;
}

ml_logical_function_definition(and) // ml_and

ml_logical_function_definition(or)  // ml_or

ml_logical_function_definition(xor) // ml_xor
