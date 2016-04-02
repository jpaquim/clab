#include "test.h"
#include "matrix.h"

char *test_matrix(void) {
    scalar array_vec[] = {1.0,2.0,3.0};
    vector vec = vector_from_array(array_vec,3);
    scalar array_mat[][2] = {{1.0,2.0},{0.0,1.0},{-1.0,1.0}};
    scalar array_mat2[][2] = {{-1.0,0.0},{3.0,1.0},{-5.0,-2.0}};
    matrix mat = matrix_from_array(*array_mat,3,2);
    matrix A = matrix_diag(vec);
    matrix B = copy_matrix(mat);
    delete_matrix(mat);
    matrix C = matrix_mtimes(A,B);
    printf("B = \n");
    print_matrix(B);
    printf("C = A*B\n");
    print_matrix(C);
    
    vector a = matrix_row(C,2);
    vector b = matrix_col(C,1);
    printf("sum of row 2: %f\n",vector_sum_elem(a));
    printf("row_max of row 2: %f\n",vector_max_elem(a));
    printf("sum of col 1: %f\n",vector_sum_elem(b));
    printf("row-wise row_maximum: \n");
    print_vector(matrix_row_max(B));
    
    matrix D = matrix_from_array(*array_mat2,3,2);
    printf("D = \n");
    print_matrix(D);
    matrix E = matrix_times(B,D);
    printf("E = B.*D\n");
    print_matrix(E);
    matrix F = matrix_transpose(E);
    printf("F = E'\n");
    print_matrix(F);
    printf("F*[1;0;0]\n");
    scalar c_array[] = {0.0,0.0,1.0};
    vector c = vector_from_array(c_array,3);
    print_vector(matrix_mtimes_vector(F,c));
    print_vector(vector_times_scalar(vector_from_matrix(F),2));
    //    print_matrix_matlab(matrix_divide(B,D));
    printf("B = \n");
    print_matrix_matlab(B);
    return NULL;
}
