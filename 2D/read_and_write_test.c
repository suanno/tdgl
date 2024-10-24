#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//#include </opt/intel/composer_xe_2013_sp1.3.174/mkl/include/fftw/fftw3.h>
#include <fftw3.h>
#include <math.h>
#include "read_write.h"
#define D 2 //Dimension of the problem
#define MAX_BUFFER_SIZE 256

#define pi  4*atan(1.0)
int main(int argc, char  *argv [ ]){
    double tmin, tspan, tmax;
    tspan = 16;

    int i, j, N;
    double dx;
    double** h;

    /* Read parameters from CMD */
    char* fileSimul;                    //Name of the simulation folder (data is red/wrote ONLY there)
    char* ptr;
    int min_args = 2;                   // Minimum Number of required arguments
    if (argc <= min_args){
        printf("Not enought arguments");
        return 0;
    }
    tspan = (double)strtod(argv[1], &ptr);
    fileSimul = argv[2];

    char save_dir[MAX_BUFFER_SIZE] = ".saves/"; strcat(save_dir, fileSimul); /* add the extension */
    char fileCinName[MAX_BUFFER_SIZE] = ""; strcat(fileCinName, save_dir); strcat(fileCinName, "/fileCin.dat");
    char state_dir[MAX_BUFFER_SIZE] = ""; strcat(state_dir, save_dir); strcat(state_dir, "/state.dat");

    /*Load initial state*/
    N = loadState(state_dir, &h, &dx, &tmin);

    //i = 1; j = 3;
    //printf("h[%d][%d] = %lf\n", i, j, h[i][j]);
    /*Read C(t)*/
    double* C;   //C[i]=C(t_i+dt)
    double* t_C; //Time of the C(t) values
    double Cprev;
    int nloop = 0;
    nloop = readC(fileCinName, &C, &t_C, &Cprev, tmin, tspan);

    /*Write state*/
    tmax = tmin + tspan;
    writeState(state_dir, h, N, dx, tmax);

    printf("Fine\n");
    free(h);
    free(C);
    free(t_C);
    
    return 1;
}