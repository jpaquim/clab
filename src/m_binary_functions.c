#include "matrix.h"

void m_check_sizes(matrix A, matrix B) {
    assert(A.m == B.m && A.n == B.n);
}

matrix m_bsxfun(binary_function f, matrix A, matrix B) {
    m_check_sizes(A, B);
    matrix C = m_zeros(A.m, A.n);
    for (size_t i = 0; i < A.m; ++i)
        for (size_t j = 0; j < A.n; ++j)
            C.ij[i][j] = f(A.ij[i][j], B.ij[i][j]);
    return C;
}

m_binary_function_definition(plus)    // m_plus

m_binary_function_definition(minus)   // m_minus

m_binary_function_definition(times)   // m_times

m_binary_function_definition(divide)  // m_divide

m_binary_function_definition(idivide) // m_idivide

m_binary_function_definition(mod)     // m_mod

m_binary_function_definition(rem)     // m_rem

m_binary_function_definition(power)   // m_power

m_binary_function_definition(max)     // m_max

m_binary_function_definition(min)     // m_min

m_binary_function_definition(atan2)   // m_atan2

matrix m_mtimes(matrix A, matrix B) {
    assert(A.n == B.m);
    matrix C = m_zeros(A.m,B.n);
    for (size_t i = 0; i < A.m; ++i)
        for (size_t k = 0; k < A.n; ++k)
            for (size_t j = 0; j < B.n; ++j)
                C.ij[i][j] += A.ij[i][k]*B.ij[k][j];
    return C;
}

matrix m_times_s(matrix A, scalar b) {
    matrix C = m_zeros(A.m,A.n);
    for (size_t i = 0; i < A.m; ++i)
        for (size_t j = 0; j < A.n; ++j)
            C.ij[i][j] = b*A.ij[i][j];
    return C;
}

vector m_mtimes_v(matrix A, vector b) {
    return v_from_m(m_mtimes(A, m_from_v(b)));
}
