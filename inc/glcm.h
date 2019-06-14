#ifndef GLCM_H
#define GLCM_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define NUM_LINES 255;
// #define NUM_SOLUMN 255;

void glcm(int **, double[24]);
void alocate_matrix(int **);
void build_glcm_matrix(int **, double **, int);
void verify_value(int, int, double **, int);
void calcular_homogeneidade(double **, double *, double *, int);
void normalize_matrix(double **, int, int);
void calcular_energia(double **,  double *, double *, int );
void calcular_contraste(double **, double *, double *, int);

#endif
