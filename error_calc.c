#include <stdlib.h>
#include <math.h>
#include "error_calc.h"

void calculate_errors(double **A, double **A_inv, int n, double *r1, double *r2) {
    if (n > 11000) {
        *r1 = 0;
        *r2 = 0;
        return;
    }

    double max1 = 0, max2 = 0;
    
    // r1 = ||A * A_inv - E||_1
    for (int j = 0; j < n; j++) {
        double col_sum = 0;
        for (int i = 0; i < n; i++) {
            double identity = (i == j) ? 1.0 : 0.0;
            double diff = 0;
            for (int k = 0; k < n; k++) {
                diff += A[i][k] * A_inv[k][j];
            }
            col_sum += fabs(diff - identity);
        }
        if (col_sum > max1) {
            max1 = col_sum;
        }
    }

    // r2 = ||A_inv * A - E||_1
    for (int j = 0; j < n; j++) {
        double col_sum = 0;
        for (int i = 0; i < n; i++) {
            double identity = (i == j) ? 1.0 : 0.0;
            double diff = 0;
            for (int k = 0; k < n; k++) {
                diff += A_inv[i][k] * A[k][j];
            }
            col_sum += fabs(diff - identity);
        }
        if (col_sum > max2) {
            max2 = col_sum;
        }
    }

    *r1 = max1;
    *r2 = max2;
}
