#include "test.h"

#include <stdio.h>

int tests_run = 0;

const char *test_all(void) {
//    mu_run_test(test_scalar);
    mu_run_test(test_matrix);
//    mu_run_test(test_vector);
//    mu_run_test(test_sample);
    return NULL;
}

int main(void) {
    const char *result = test_all();
    if (result != NULL)
        printf("%s\n", result);
    else
        printf("All Tests Passed\n");
    printf("Tests run: %d\n", tests_run);
    return result != NULL;
}
