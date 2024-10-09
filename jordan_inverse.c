#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "jordan_inverse.h"
#include "matrix_output.h"

int jordan_inverse(int n, double **A, double **A_inv) {
    double EPS = 0.00001;
    double c, pivot;
    double* tmp;
    int row, sel;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A_inv[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int col = 0; col < n; ++col) {
        row = col;
        sel = row;
        for (int i = row; i < n; ++i) {
            if (fabs(A[i][col]) > fabs(A[sel][col])) {
                sel = i;
            }
        }

        if (fabs(A[sel][col]) < EPS) {
            return 1;
        }

        if (sel != row) {
            tmp = A[sel];
            A[sel] = A[row];
            A[row] = tmp;

            tmp = A_inv[sel];
            A_inv[sel] = A_inv[row];
            A_inv[row] = tmp;
        }
 
        for (int i = 0; i < n; ++i) {
            if (i != row) {
                c = A[i][col] / A[row][col];
                for (int j = 0; j < n; ++j) {
                    A[i][j] -= A[row][j] * c;
                    A_inv[i][j] -= A_inv[row][j] * c;
                }
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        pivot = A[j][j];
        for (int i = 0; i < n; ++i) {
            A_inv[j][i] /= pivot;
        }
    }

    return 0;
}
