#include <stdio.h>
#include <stdlib.h>
#include "jordan_inverse.h"
#include "matrix_output.h"

double absd(double x) {
    printf("abs(%lf) = %lf\n", x, (x >= 0.0 ? x : -x));
    return x >= 0.0 ? x : -x;
}

int jordan_inverse(int n, double **A, double **A_inv) {
    double EPS = 0.00001;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A_inv[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int col = 0; col < n; ++col) {
        int row = col;
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (absd(A[i][col]) > absd(A[sel][col])) {
                sel = i;
            }
        }

        if (absd(A[sel][col]) < EPS) {
            return 1;
        }

        if (sel != row) {
            double* tmp = A[sel];
            A[sel] = A[row];
            A[row] = tmp;

            tmp = A_inv[sel];
            A_inv[sel] = A_inv[row];
            A_inv[row] = tmp;
        }
 
        for (int i = 0; i < n; ++i) {
            if (i != row) {
                double c = A[i][col] / A[row][col];
                for (int j = 0; j < n; ++j) {
                    A[i][j] -= A[row][j] * c;
                    A_inv[i][j] -= A_inv[row][j] * c;
                }
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        double pivot = A[j][j];
        for (int i = 0; i < n; ++i) {
            A_inv[j][i] /= pivot;
        }
    }

    return 0;
}
