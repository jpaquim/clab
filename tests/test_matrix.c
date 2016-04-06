#include "test.h"
#include "matrix.h"

const char *test_matrix(void) {
    // test m_from_array
    scalar array_A[] = {1.0, 2.0, 3.0,
                        4.0, 5.0, 6.0};
    matrix A = m_from_array(array_A, 2, 3);
    m_display(A);
    mu_assert(A.m == 2, "wrong number of rows");
    mu_assert(A.n == 3, "wrong number of cols");
    for (size_t i = 0; i < A.m; ++i)
        for (size_t j = 0; j < A.n; ++j)
            mu_assert(A.ij[i][j] == array_A[i*3+j], "wrong matrix data");
    
    // test ml_eq
    scalar array_A_[] = {1.0, 2.0, 2.0,
                         4.0, 4.0, 6.0};
    matrix A_ = m_from_array(array_A_, 2, 3);
    scalar_l array_eq[] = {1, 1, 0,
                           1, 0, 1};
    m_display(A_);
    matrix_l eq = ml_eq(A, A_);
    ml_display(eq);
    mu_assert(eq.m == 2, "wrong number of rows");
    mu_assert(eq.n == 3, "wrong number of cols");
    for (size_t i = 0; i < eq.m; ++i)
        for (size_t j = 0; j < eq.n; ++j)
            mu_assert(eq.ij[i][j] == array_eq[i*3+j], "wrong matrix data ml_eq");
    
    // test m_isequal
    m_display(A);
    m_display(m_from_array(array_A, 2, 3));
    mu_assert(m_isequal(A, m_from_array(array_A, 2, 3)), "wrong m_isequal");
    mu_assert(!m_isequal(A, A_), "wrong m_isequal negation");

    // m_from_array and m_isequal valid, use m_isequal(..., m_from_array(...))
    
    // test m_copy
    matrix A_copy = m_copy(A);
    mu_assert(m_isequal(A, A_copy), "matrix copied incorrectly");
    
    // test m_delete
    m_delete(&A_copy);
    mu_assert(m_isempty(A_copy), "matrix not empty");
    
    // test m_zeros
    scalar array_zeros[] = {0.0, 0.0, 0.0,
                            0.0, 0.0, 0.0};
    matrix zeros = m_zeros(2, 3);
    m_display(zeros);
    mu_assert(m_isequal(zeros, m_from_array(array_zeros, 2, 3)), "zeros != 0");
    
    // test m_ones
    scalar array_ones[] = {1.0, 1.0, 1.0,
                           1.0, 1.0, 1.0};
    matrix ones = m_ones(2, 3);
    m_display(ones);
    mu_assert(m_isequal(ones, m_from_array(array_ones, 2, 3)), "ones != 1");
    
    // test m_eye
    scalar array_eye[] = {1.0, 0.0, 0.0,
                          0.0, 1.0, 0.0,
                          0.0, 0.0, 1.0};
    matrix eye = m_eye(3);
    m_display(eye);
    mu_assert(m_isequal(eye, m_from_array(array_eye, 3, 3)),
              "error: m_eye != eye(3)");
    
    // test m_diag
    scalar array_b[] = {1.0, 2.0, 3.0};
    scalar array_B[] = {1.0, 0.0, 0.0,
                        0.0, 2.0, 0.0,
                        0.0, 0.0, 3.0};
    vector b = v_from_array(array_b, 3);
    matrix B = m_diag(b);
    m_display(B);
    mu_assert(m_isequal(B, m_from_array(array_B, 3, 3)),
              "error: B != diag(b)");
    
    // test m_repmat
    scalar array_unit[] = {1.0, 0.0};
    scalar array_rep[] = {1.0, 0.0, 1.0, 0.0,
                          1.0, 0.0, 1.0, 0.0,
                          1.0, 0.0, 1.0, 0.0};
    matrix unit = m_from_array(array_unit, 1, 2);
    matrix rep = m_repmat(unit, 3, 2);
    m_display(rep);
    mu_assert(m_isequal(rep, m_from_array(array_rep, 3, 4)), "wrong m_repmat");

    // test ml_all_row
    scalar_l array_C[] = {1, 1, 1,
                          1, 0, 0,
                          1, 0, 1,
                          1, 0, 0};
    matrix_l C = ml_from_array(array_C, 4, 3);
    ml_display(C);
    scalar_l array_all_row[] = {1,
                                0,
                                0,
                                0};
    matrix_l all_row = ml_all_row(C);
    ml_display(all_row);
    mu_assert(ml_isequal(all_row, ml_from_array(array_all_row, 4, 1)),
              "err: all_row");

    // test ml_all_col
    scalar_l array_all_col[] = {1, 0, 0};
    matrix_l all_col = ml_all_col(C);
    ml_display(all_col);
    mu_assert(ml_isequal(all_col, ml_from_array(array_all_col, 1, 3)),
              "error: all_col");
    
    // test ml_all_elt
    mu_assert(ml_all_elt(C) == 0, "error: all_elt");
    mu_assert(ml_all_elt(ml_true(3, 3)) == 1.0, "error: all_elt");
    
    return NULL;
}
