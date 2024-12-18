#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D 2
#define pi 4*atan(1.0)
#define BUF_SIZE 65536
#define MAX_BUFFER_SIZE 256

double calcq2ave(double** hfr, double** hfi, double** q2, int N){
    double weight_sum, q2ave;
    int i, j;
    q2ave = 0; weight_sum = 0;
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            /*Minus sign because teh variable q2 is the observable -q2*/
            q2ave = q2ave + q2[i][j]*(hfr[i][j]*hfr[i][j] + hfi[i][j]*hfi[i][j]);
            weight_sum = weight_sum + (hfr[i][j]*hfr[i][j] + hfi[i][j]*hfi[i][j]);
        }
    }
    q2ave = q2ave/(weight_sum*D);
    return q2ave;
}

double calcCauchyCrofton(double** u, int N, double dx){
    /*Extimate the (total) interface(s) lenght by using the Cauchy-Croft formula */

    int i, j, num_crossings;
    double average_lenght, uprev;
    average_lenght = 0;
    //Horizontal lines, spaced dx
    num_crossings = 0;
    for (i = 0; i < N; i++){
        uprev = u[i][0];
        for (j = 1; j < N; j++){
            if (u[i][j]*uprev < 0){
                num_crossings = num_crossings + 1;
            }
            uprev = u[i][j];
        }
    }
    average_lenght = average_lenght + 0.5*num_crossings*dx*(pi/4);
    //Vertical lines, spaced dx
    num_crossings = 0;
    for (i = 0; i < N; i++){
        uprev = u[0][i];
        for (j = 1; j < N; j++){
            if (u[j][i]*uprev < 0){
                num_crossings = num_crossings + 1;
            }
            uprev = u[j][i];
        }
    }
    average_lenght = average_lenght + 0.5*num_crossings*dx*(pi/4);
    //pi/4 lines, spaced sqrt(2)*dx
    num_crossings = 0;
    for (i = 1; i < N; i++){
        uprev = u[0][i];
        j = 1;
        while (j <= i){
            if (u[j][i-j]*uprev < 0){
                num_crossings = num_crossings + 1;
            }
            uprev = u[j][i-j];
            j = j + 1;
        }
    }
    average_lenght = average_lenght + 0.5*num_crossings*(sqrt(2)*dx)*(pi/4);
    //pi*3/4 lines, spaced sqrt(2)*dx
    num_crossings = 0;
    for (i = 1; i < N; i++){
        uprev = u[N-1][i];
        j = 1;
        while (j <= i){
            if (u[N-1-j][i-j]*uprev < 0){
                num_crossings = num_crossings + 1;
            }
            uprev = u[N-1-j][i-j];
            j = j + 1;
        }
    }
    average_lenght = average_lenght + 0.5*num_crossings*(sqrt(2)*dx)*(pi/4);

    return average_lenght/4;
}

double calcDW(double** ghx, double** ghy, double dx, int N){
        /*Compute the L^2/integral of |Grad u|^2. This value, times the thickness of the interface, gives the characteristic lenght \ell_DW*/
        //Remember that FFTW, when performing both DFT and IDFT, does not normalize the data by any factor (nor sqrt(N) nor N in just one of the two)
        double integ_grad2 = 0;
        double L = (double)N*dx;
        for(int i=0;i<N;i++) {
            for(int j=0;j<N;j++) {
                /*We DO NOT take a sqrt for better resolution of the peak position*/
                integ_grad2 = integ_grad2 + (ghx[i][j]*ghx[i][j] + ghy[i][j]*ghy[i][j])*(dx*dx);
            }
        }
        //We do not save the integral of the grad2, but the fraction: TotalArea/integGrad2
        integ_grad2 = (L*L)/integ_grad2;

        return integ_grad2;
}

int calcstructure_fact(double** ufr, double** ufi, int N, double* structure_fac){
    /* Consider S(qx,qy) along the horizontal directions passing through (0, 0) and take the average of the two functions */
    int i,j;
    // Horizontal
    i = 0;
    for (j = 0; j < N; j++){
        structure_fac[j] = ufr[i][j]*ufr[i][j]+ufi[i][j]*ufi[i][j];
    }
    // Vertical
    j = 0;
    for (i = 0; i < N; i++){
        structure_fac[i] = (structure_fac[i] + ufr[i][j]*ufr[i][j]+ufi[i][j]*ufi[i][j])/2;
    }

    return 1;
}

int save_observable(FILE* dest_file, char* save_dir, char* obs_name, double* obsx, double* obsy, int len, int append){
    double x, y;
    char obs_dir[MAX_BUFFER_SIZE] = "";
    strcat(obs_dir, save_dir);
    strcat(obs_dir, "/");
    strcat(obs_dir, obs_name);
	if (append == 1)
    	dest_file = fopen(obs_dir, "a");
	else
    	dest_file = fopen(obs_dir, "w");
    for (int i=0; i<len; i++){
        x = obsx[i];
        y = obsy[i];
        fprintf(dest_file, "%.5f %.20f\n", x, y);
    }
    fclose(dest_file);
    return 1;
}

int count_lines(FILE* file)
{
    char buf[BUF_SIZE];
    int counter = 0;
    for(;;)
    {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;

        int i;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (feof(file))
            break;
    }

    return counter;
}
