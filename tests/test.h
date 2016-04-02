#ifndef	TEST_H
#define TEST_H

// MinUnit - a minimal unit testing framework for C

#define mu_assert(message, test) do { \
    if (!(test)) return message;      \
} while (0)

#define mu_run_test(test) do { \
    char *message = test();    \
    tests_run++;               \
    if (message)               \
        return message;        \
} while (0)

extern int tests_run;

// test functions
char *test_scalar(void);
char *test_vector(void);
char *test_matrix(void);
char *test_sample(void);
char *test_all(void);

#endif
