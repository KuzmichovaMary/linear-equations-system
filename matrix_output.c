#include <stdio.h>
#include "matrix_output.h"

void print_matrix(double **matrix, int n, int r) {
    int rows = (r < n) ? r : n;
    int cols = (r < n) ? r : n;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf(" %10.3e", matrix[i][j]);
        }
        printf("\n");
    }
}
