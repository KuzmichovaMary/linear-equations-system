#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "error_calc.h"

void calculate_errors(double **A, double **A_inv, int n, double *r1, double *r2) {
    double diff1, diff2, col_sum1, col_sum2, max1, max2;
    if (n > 11000) {
        *r1 = 0;
        *r2 = 0;
        return;
    }

    max1 = 0, max2 = 0;
    
    // r1 = ||A * A_inv - E||_1
    for (int j = 0; j < n; j++) {
        col_sum1 = 0;
        col_sum2 = 0;
        for (int i = 0; i < n; i++) {
            diff1 = 0;
            diff2 = 0;
            for (int k = 0; k < n; k++) {
                diff1 += A[i][k] * A_inv[k][j];
                diff2 += A_inv[i][k] * A[k][j];
            }
            if (i == j) {
                diff1 -= 1;
                diff2 -= 1;
            }
            col_sum1 += fabs(diff1);
            col_sum2 += fabs(diff2);
        }
        if (col_sum1 > max1) {
            max1 = col_sum1;
        }
        if (col_sum2 > max2) {
            max2 = col_sum2;
        }
    }

    *r1 = max1;
    *r2 = max2;
}
