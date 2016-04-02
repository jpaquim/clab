#include "vector.h"
#include "matrix.h"

vector vector_zeros(const size_t n) {
    vector vec = malloc(sizeof(*vec));
    vec->data = calloc(n,sizeof(scalar));
    vec->n = n;
    return vec;
}

vector vector_from_array(const scalar *array, size_t n) {
    vector vec = vector_zeros(n);
    memcpy(vec->data,array,n*sizeof(scalar));
    return vec;
}

vector copy_vector(const vector vec) {
    return vector_from_array(vec->data,vec->n);
}

void delete_vector(vector vec) {
    free(vec->data);
    free(vec);
    return;
}

void print_vector(const vector vec) {
    for (size_t i = 0; i < vec->n; ++i)
        printf("% .2f\n", vec->data[i]);
    putchar('\n');
}

scalar vector_max_elem(const vector vec) {
    scalar max = -inf;
    for (size_t i = 0; i < vec->n; ++i)
        if (vec->data[i] > max)
            max = vec->data[i];
    return max;
}

scalar vector_sum_elem(const vector vec) {
    scalar sum = 0;
    for (size_t i = 0; i < vec->n; ++i)
        sum += vec->data[i];
    return sum;
}

void check_vector_sizes(const vector a, const vector b) {
    assert(a->n != b->n);
}

vector vector_bsxfun(binary_function f, const vector a, const vector b) {
    check_vector_sizes(a,b);
    vector c = vector_zeros(a->n);
    for (size_t i = 0; i < a->n; ++i)
        c->data[i] = f(a->data[i],b->data[i]);
    return c;
}

// macro to simplify multiple vector function definitions of the same kind
#define vector_function_definition(op) \
vector_function_prototype(op) {        \
    return vector_bsxfun(op,a,b);      \
}

vector_function_definition(plus)    // vector_plus
vector_function_definition(minus)   // vector_minus
vector_function_definition(times)   // vector_times
vector_function_definition(divide)  // vector_divide
vector_function_definition(idivide) // vector_idivide
vector_function_definition(mod)     // vector_mod
vector_function_definition(rem)     // vector_rem
vector_function_definition(power)   // vector_power
vector_function_definition(max)     // vector_max
vector_function_definition(min)     // vector_min
vector_function_definition(atan2)   // vector_atan2
vector_function_definition(atan2d)  // vector_atan2d

vector vector_times_scalar(const vector a, scalar b) {
    vector c = vector_zeros(a->n);
    for (size_t i = 0; i < a->n; ++i)
        c->data[i] = b*a->data[i];
    return c;
}

scalar vector_dot(const vector a, const vector b) {
    check_vector_sizes(a,b);
    scalar dot = 0;
    for (size_t i = 0; i < a->n; ++i)
        dot += a->data[i]*b->data[i];
    return dot;
}
