#include "matrix.h"

void m_disp(matrix mat) {
    for (size_t i = 0; i < mat.m; ++i) {
        for (size_t j = 0; j < mat.n; ++j)
            printf("   % .4f", mat.ij[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

//#define m_display(mat) do {   \
//    putchar('\n');            \
//    printf("%s =\n\n", #mat); \
//    m_disp(mat);              \
//} while (0)

void m_print_matlab(matrix mat) {
    putchar('[');
    for (size_t i = 0; i < mat.m; ++i) {
        if (i != 0)
            putchar(' ');
        for (size_t j = 0; j < mat.n; ++j) {
            printf("% .4f", mat.ij[i][j]);
            if (j != mat.n-1)
                printf("  ");
        }
        if (i != mat.m-1)
            printf(";\n");
    }
    printf("];\n");
}
