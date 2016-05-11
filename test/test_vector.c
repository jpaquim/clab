#include "test.h"
#include "vector.h"

const char *test_vector(void) {
    scalar array_a[] = {1.0,2.0,3.0};
    vector a = v_from_array(array_a,3);
    mu_assert(a.n == 3, "error: wrong vector size, a.n != 3");
    for (size_t i = 0; i < a.n; ++i)
        mu_assert(a.i[i] == array_a[i], "error: wrong vector data");
    v_print(a);
	return NULL;
}
