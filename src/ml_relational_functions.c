#include "matrix.h"

matrix_l ml_bsxfun_rel(relational_function f, matrix A, matrix B) {
    m_check_sizes(A, B);
    matrix_l rel = ml_false(A.m, A.n);
    for (size_t i = 0; i < A.m; ++i)
        for (size_t j = 0; j < A.n; ++j)
            rel.ij[i][j] = f(A.ij[i][j], B.ij[i][j]);
    return rel;
}

//#define ml_relational_function_definition(op) \
//ml_relational_function_prototype(op) {        \
//  return ml_bsxfun_rel(op, A, B);             \
//}

ml_relational_function_definition(eq) // ml_eq

ml_relational_function_definition(ne) // ml_ne

ml_relational_function_definition(lt) // ml_lt

ml_relational_function_definition(le) // ml_le

ml_relational_function_definition(gt) // ml_gt

ml_relational_function_definition(ge) // ml_ge


scalar_l m_isequal(matrix A, matrix B) {
    if (A.m != B.m || A.n != B.n)
        return false;
    return ml_all_elt(ml_eq(A, B));
}

scalar_l ml_isequal(matrix_l A, matrix_l B) {
    if (A.m != B.m || A.n != B.n)
        return false;
    for (size_t i = 0; i < A.m; ++i)
        for (size_t j = 0; j < A.n; ++j)
            if (A.ij[i][j] != B.ij[i][j])
                return false;
    return true;
}
