#ifndef	TEST_H
#define TEST_H

// MinUnit - a minimal unit testing framework for C

#define mu_assert(test, message) do { \
    if (!(test)) return message;      \
} while (0)

#define mu_run_test(test) do {    \
    const char *message = test(); \
    tests_run++;                  \
    if (message)                  \
        return message;           \
} while (0)

extern int tests_run;

// test functions
const char *test_scalar(void);
const char *test_vector(void);
const char *test_matrix(void);
const char *test_sample(void);
const char *test_all(void);

#endif
