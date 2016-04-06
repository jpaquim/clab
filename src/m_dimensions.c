#include "matrix.h"

scalar_l m_isempty(matrix mat) {
    matrix empty = m_empty();
    if (mat.m == empty.m &&
        mat.n == empty.n &&
        mat.ij == empty.ij)
        return true;
    else
        return false;
}
