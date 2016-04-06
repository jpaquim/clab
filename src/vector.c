#include "vector.h"
#include "matrix.h"

vector v_zeros(size_t n) {
    vector vec;
    vec.i = calloc(n,sizeof(scalar));
    vec.n = n;
    return vec;
}

vector v_from_array(scalar *array, size_t n) {
    vector vec = v_zeros(n);
    memcpy(vec.i,array,n*sizeof(scalar));
    return vec;
}

vector v_copy(vector vec) {
    return v_from_array(vec.i,vec.n);
}

void v_delete(vector vec) {
    free(vec.i);
    return;
}

void v_print(vector vec) {
    for (size_t i = 0; i < vec.n; ++i)
        printf("% .2f\n", vec.i[i]);
    putchar('\n');
}

scalar v_max_elem(vector vec) {
    scalar max = -Inf;
    for (size_t i = 0; i < vec.n; ++i)
        if (vec.i[i] > max)
            max = vec.i[i];
    return max;
}

scalar v_sum_elem(vector vec) {
    scalar sum = 0;
    for (size_t i = 0; i < vec.n; ++i)
        sum += vec.i[i];
    return sum;
}

void v_check_sizes(vector a, vector b) {
    assert(a.n != b.n);
}

vector v_bsxfun(binary_function f, vector a, vector b) {
    v_check_sizes(a,b);
    vector c = v_zeros(a.n);
    for (size_t i = 0; i < a.n; ++i)
        c.i[i] = f(a.i[i],b.i[i]);
    return c;
}

// macro to simplify multiple vector function definitions of the same kind
#define v_function_definition(op) \
v_function_prototype(op) {        \
    return v_bsxfun(op,a,b);      \
}

v_function_definition(plus)    // v_plus
v_function_definition(minus)   // v_minus
v_function_definition(times)   // v_times
v_function_definition(divide)  // v_divide
v_function_definition(idivide) // v_idivide
v_function_definition(mod)     // v_mod
v_function_definition(rem)     // v_rem
v_function_definition(power)   // v_power
v_function_definition(max)     // v_max
v_function_definition(min)     // v_min
v_function_definition(atan2)   // v_atan2
v_function_definition(atan2d)  // v_atan2d

vector v_times_scalar(vector a, scalar b) {
    vector c = v_zeros(a.n);
    for (size_t i = 0; i < a.n; ++i)
        c.i[i] = b*a.i[i];
    return c;
}

scalar v_dot(vector a, vector b) {
    v_check_sizes(a,b);
    scalar dot = 0;
    for (size_t i = 0; i < a.n; ++i)
        dot += a.i[i]*b.i[i];
    return dot;
}
