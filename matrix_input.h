#ifndef MATRIX_INPUT_H
#define MATRIX_INPUT_H

double **allocate_matrix(int n);
void free_matrix(double **matrix, int n);
int read_matrix_from_file(const char *filename, double **matrix, int n);
void initialize_matrix_formula(double **matrix, int n, int s);
double f(int s, int n, int i, int j);

#endif
