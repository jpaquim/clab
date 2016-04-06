#include "matrix_l.h"

void ml_disp(matrix_l mat) {
    for (size_t i = 0; i < mat.m; ++i) {
        for (size_t j = 0; j < mat.n; ++j)
            printf("   %d", mat.ij[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

//#define ml_display(mat) do {   \
//    putchar('\n');            \
//    printf("%s =\n\n", #mat); \
//    ml_disp(mat);              \
//} while (0)

void ml_print_matlab(matrix_l mat) {
    putchar('[');
    for (size_t i = 0; i < mat.m; ++i) {
        if (i != 0)
            putchar(' ');
        for (size_t j = 0; j < mat.n; ++j) {
            printf("% df", mat.ij[i][j]);
            if (j != mat.n-1)
                printf("  ");
        }
        if (i != mat.m-1)
            printf(";\n");
    }
    printf("];\n");
}
