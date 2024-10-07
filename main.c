#include <stdio.h>
#include <stdlib.h>
#include "matrix_input.h"
#include "jordan_inverse.h"
#include "matrix_output.h"
#include "error_calc.h"
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <n> <r> <s> [<filename>]\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int r = atoi(argv[2]);
    int s = atoi(argv[3]);

    double **A = allocate_matrix(n);
    double **A_inv = allocate_matrix(n);
    
    if (s == 0 && argc == 5) {
        const char *filename = argv[4];
        if (read_matrix_from_file(filename, A, n) != 0) {
            printf("%s : Task = 18 Res1 = -1 Res2 = -1 T1 = 0 T2 = 0 S = %d N = %d\n", argv[0], s, n);
            return 1;
        }
    } else {
        initialize_matrix_formula(A, n, s);
    }

    print_matrix(A, n, r);

    clock_t start = clock();
    int res = jordan_inverse(n, A, A_inv);
    clock_t end = clock();
    double t1 = (double)(end - start) / CLOCKS_PER_SEC;
    if (res != 0) {
        printf("%s : Task = 18 Res1 = -1 Res2 = -1 T1 = %.2f T2 = 0 S = %d N = %d\n", argv[0], t1, s, n);
        return 1;
    }

    start = clock();
    double r1, r2;
    calculate_errors(A, A_inv, n, &r1, &r2);
    end = clock();
    double t2 = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%s : Task = 18 Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n", argv[0], r1, r2, t1, t2, s, n);

    print_matrix(A_inv, n, r);

    free_matrix(A, n);
    free_matrix(A_inv, n);

    return 0;
}
