#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>

#define D 1 //Dimension of the problem
#define pi 4*atan(1.0)

double calckink_dist(double* x, double* u, int N, double dx);
double calcq2ave(double* ufr, double* ufi, double* d2coef, int N, double dx);
double calcelllDW(double* ufr, double* ufi, double* d2coef, int N, double dx);
int calcstructure_fact(double* ufr, double* ufi, int N, double* structure_fac);
int save_observable(FILE* dest_file, char* filename, double* obsx, double* obsy, int len, int append);

#endif