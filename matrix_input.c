#include <stdio.h>
#include <stdlib.h>
#include "matrix_input.h"

double **allocate_matrix(int n) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    return matrix;
}

void free_matrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int read_matrix_from_file(const char *filename, double **matrix, int n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &matrix[i][j]) != 1) {
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

void initialize_matrix_formula(double **matrix, int n, int s) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = f(s, n, i, j);
        }
    }
}

double f(int s, int n, int i, int j) {
    switch (s) {
        case 1:
            return n - (i > j ? i : j) + 1;
        case 2:
            return (i > j ? i : j);
        case 3:
            return abs(i - j);
        case 4:
            return 1.0 / (i + j - 1);
        default:
            return 0.0;
    }
}