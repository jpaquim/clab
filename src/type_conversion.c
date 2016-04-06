#include "matrix.h"
#include "vector.h"

matrix m_from_v(vector vec) {
    return m_from_array(vec.i,vec.n,1);
}

vector v_from_m(matrix mat) {
    return v_from_array(*mat.ij,mat.m*mat.n);
}

scalar s_from_m(matrix mat) {
    return mat.ij[0][0];
}

scalar_l l_from_ml(matrix_l mat) {
    return mat.ij[0][0];
}

scalar_l l_from_m(matrix mat) {
    return mat.ij[0][0] != 0.0;
}
