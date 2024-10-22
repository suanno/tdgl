#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//#include </opt/intel/composer_xe_2013_sp1.3.174/mkl/include/fftw/fftw3.h>
#include <fftw3.h>
#include <math.h>
#include "observables.h"
#define D 2 //Dimension of the problem
#define MAX_BUFFER_SIZE 256

#define pi  4*atan(1.0)
int main(int argc, char  *argv [ ]){

double temp;
int N; double dx;                   //Space
double dt, tmin, tmax, tspan;       //Time
                                    /*  tmin: Initial time(of the initial state)
                                        tmax: Final time (of the final state)
                                    */
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


int read_from_top = 0;             // Read fileCin.dat from t=0 instead of t=t_min (initial time of the simulation)
int loop_read = 0;                 // If the time reaches a value t so large that is not contained in fileCin.dat, it continues to read the file from the top (t=0)
if (argc > min_args + 1)
    read_from_top = (int)strtod(argv[3], &ptr);
if (argc > min_args + 2)
    loop_read = (int)strtod(argv[3], &ptr);

char save_dir[MAX_BUFFER_SIZE] = ".saves/"; strcat(save_dir, fileSimul); /* add the extension */
char fileCinName[MAX_BUFFER_SIZE] = ""; strcat(fileCinName, save_dir); strcat(fileCinName, "/fileCin.dat");


/* Read parameters from the state's file "state.dat" */
char state_dir[MAX_BUFFER_SIZE] = ""; strcat(state_dir, save_dir); strcat(state_dir, "/state.dat");
FILE *fileinit;
fileinit = fopen(state_dir, "r");
/*First line contains parameters*/
fscanf(fileinit, "%d %lf %lf\n", &N, &tmin, &dx);
//fclose(fileinit);


/*Read C(t) from file*/
FILE* fileCin;
double Cprev;   /*Last value of C in the previous simulation*/
double time_fileCin, C_fileCin;
/*CONVENTION: C[i]=C(t_i + dt)*/
//Find the size of C(t) array
time_fileCin = 0; C_fileCin = 0;
int nloop = 0; int loop_read_iterations = 0; double tfinal = 0;
fileCin = fopen(fileCinName, "r");
while (time_fileCin+loop_read_iterations*tfinal <= tmin + tspan){
    /*If you reach the end of fileCin [if t_state > t_finalC]*/
    if(fscanf(fileCin, "%lf %lf \n", &time_fileCin, &C_fileCin) == EOF){
		if (loop_read == 1){
			rewind(fileCin);
            loop_read_iterations = loop_read_iterations + 1;
            fscanf(fileCin, "%lf %lf \n", &time_fileCin, &C_fileCin);
        }else{
            printf("fileCin.dat is too short! Think to enable the loop reading of fileCin.dat");
            fclose(fileCin);
            return 0;
        }
	}
    if (tfinal < time_fileCin)
        tfinal = time_fileCin;
    if (time_fileCin > tmin){
        nloop = nloop + 1;
    }
}
fclose(fileCin);

/*Bring the pointer in the fileCin file to the right row*/
double* C = malloc(nloop*sizeof(double));   //C[i]=C(t_i+dt)
double* t_C = malloc(nloop*sizeof(double));  //Time of the C(t) values
time_fileCin = 0; C_fileCin = 0;
fileCin = fopen(fileCinName, "r");
while (time_fileCin <= tmin){
    Cprev = C_fileCin;
    /*If you reach the end of fileCin [if t_state > t_finalC]*/
    if(fscanf(fileCin, "%lf %lf \n", &time_fileCin, &C_fileCin) == EOF){
		if (loop_read == 1){
			rewind(fileCin);
            fscanf(fileCin, "%lf %lf \n", &time_fileCin, &C_fileCin);
        }else{
            printf("fileCin.dat is too short! Think to enable the loop reading of fileCin.dat");
            fclose(fileCin);
            return 0;
        }
	}
}
//printf("diff = %f\n", tmin-time_fileCin);
C[0] = C_fileCin;
t_C[0] = time_fileCin;
printf("Reading C(t) from file. From t = %lf\n", time_fileCin);
//printf("nloop = %d\n",nloop);
int i;
for (i = 1; i < nloop; i++){
    /*If you reach the end of fileCin [if t_state > t_finalC]*/
    if(fscanf(fileCin, "%lf %lf \n", &time_fileCin, &C_fileCin) == EOF){
		if (loop_read == 1){
			rewind(fileCin);
            fscanf(fileCin, "%lf %lf \n", &time_fileCin, &C_fileCin);
        }else{
            printf("fileCin.dat is too short! Think to enable the loop reading of fileCin.dat");
            fclose(fileCin);
            return 0;
        }
	}
    C[i] = C_fileCin;
    t_C[i] = time_fileCin;
}
printf("Finish reading C(t) from file. Until t = %lf\n", time_fileCin);
fclose(fileCin);



/* Allocate memory for the state's variables */
double x, y, z;
// h(x) and its FFT
double** h = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		h[i] = malloc(N * sizeof(double));
double** hfr = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		hfr[i] = malloc(N * sizeof(double));
double** hfi = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		hfi[i] = malloc(N * sizeof(double));
double** hdt = malloc(N*sizeof(double*));
// h(x) at time t+dt and its FFT
for(i = 0; i < N; i++)
		hdt[i] = malloc(N * sizeof(double));
double** hdtfr = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		hdtfr[i] = malloc(N * sizeof(double));
double** hdtfi = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		hdtfi[i] = malloc(N * sizeof(double));
// h^3(x) and its FFT
double** hc = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		hc[i] = malloc(N * sizeof(double));
double** hcfr = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		hcfr[i] = malloc(N * sizeof(double));
double** hcfi = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		hcfi[i] = malloc(N * sizeof(double));
// q^2 array
double** q2 = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		q2[i] = malloc(N * sizeof(double));
double** integ_coef = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		integ_coef[i] = malloc(N * sizeof(double));
// q=(qx,qy) times F{u(x,y)}(qx,qy) (scalar); need to compute the gradient (h_x, h_y)
double** qxhfr = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		qxhfr[i] = malloc(N * sizeof(double));
double** qxhfi = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		qxhfi[i] = malloc(N * sizeof(double));
double** qyhfr = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		qyhfr[i] = malloc(N * sizeof(double));
double** qyhfi = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		qyhfi[i] = malloc(N * sizeof(double));
// h_x and h_y
double** ghx = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		ghx[i] = malloc(N * sizeof(double));
double** ghy = malloc(N*sizeof(double*));
for(i = 0; i < N; i++)
		ghy[i] = malloc(N * sizeof(double));
// qfr contains the discrete values available for qx (or qy)
double* ffr = malloc(N*sizeof(double));
double* qfr = malloc(N*sizeof(double));
// Size of the (real-space) simulation lattice
double L = N*dx;


/*Build q-space lattice*/
int j, k;
for (i=1; i<(N/2); i++){
ffr[i]=i;
ffr[N-i]=-i;
}
ffr[0]=0;
ffr[N/2]=N/2;
for (i=0; i<N; i++){
qfr[i]=ffr[i]*2*pi/N;
}
// Calculate the values of q2
for (i=0; i<N; i++){
    for (j=0; j<N; j++){
        q2[i][j]= (qfr[i]*qfr[i]+qfr[j]*qfr[j])/(dx*dx);
    }
}

/*Load initial state*/
for (i=0; i<N; i++){
    for (j=0; j<N; j++){
        fscanf(fileinit, "%lf %lf %lf\n", &x, &y, &z);
        h[i][j]=z;
        /*printf("u[%d][%d] = %.2lf\n", i, j, h[i][j]);*/
    }
}
fclose(fileinit);   /*Only Now: you can eventually close the state file*/


/*Define observables to track over time*/
int num_saves = 1000; /*Save the observable only at num_saves equispaced instants*/
if (nloop < num_saves)
    num_saves = nloop;
int index_saves = 0;
double* Times = malloc(num_saves*sizeof(double)); /*Times of saves*/

/*Space average of U*/
FILE *fileAveout;
double* Ave = malloc(num_saves*sizeof(double)); /*Average magnetization*/
double* q2Ave = malloc(num_saves*sizeof(double)); /*Average magnetization*/
/*Radius (of a circular island)*/
FILE *fileRadiout;
double* integ_grad2 = malloc(num_saves*sizeof(double)); /*Average magnetization*/
double* R2 = malloc(num_saves*sizeof(double)); /*Average of R2 weighted on grad2*/
double weight_sum = 0;  /*Sum of the weights*/


/* FFTW STUFF */
/* Prepare FFT Routines */
// initialize threads for fft
fftw_init_threads();

fftw_complex *in, *out;
fftw_plan pf, pb;
in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N*N);
out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N*N);
// create plans with threads
fftw_plan_with_nthreads(omp_get_max_threads());
// plan for forward transform
pf = fftw_plan_dft_2d(N,N,in,out,FFTW_FORWARD,FFTW_ESTIMATE);
// pf = fftw_plan_dft_r2c_2d(N,N,in,out,FFTW_ESTIMATE);
// plan for backward transform
pb = fftw_plan_dft_2d(N,N,in,out,FFTW_BACKWARD,FFTW_ESTIMATE);
// pb = fftw_plan_dft_c2r_2d(N,N,in,out,FFTW_ESTIMATE);
//TUNG: end of adding variables for fft


printf("\n Starting evolution...\n");

/* EVOLUTION CODE */
double time = tmin;
int loop = 0;
printf("Number time steps going to simulate = %d\n", nloop);
for(loop=0;loop<nloop;loop++) {
    dt = t_C[loop]-time;
    //printf("dt = %lf\n",dt);
    time = time + dt;
    #pragma omp parallel for //seulement pour les grands systèmes
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            integ_coef[i][j]=1-dt*C[loop]/2+dt*q2[i][j]/2;
        }
    }

    /*FFT of h(x,y)->H(qx,qy)*/
    #pragma omp parallel for //seulement pour les grands systèmes
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            in[i*N+j][0] = h[i][j];
            in[i*N+j][1] = 0.0;
        }
    }
    fftw_execute(pf);
    #pragma omp parallel for //seulement pour les grands systèmes
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            hfr[i][j] = out[i*N+j][0];
            hfi[i][j] = out[i*N+j][1];
        }
    }

    /*FFT of h3(x,y)->H3(qx,qy)*/
    #pragma omp parallel for //seulement pour les grands systèmes
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            hc[i][j] = h[i][j]*h[i][j]*h[i][j];
            in[i*N+j][0] = hc[i][j];
            in[i*N+j][1] = 0.0;
        }
    }
    fftw_execute(pf);
    #pragma omp parallel for //seulement pour les grands systèmes
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            hcfr[i][j] = out[i*N+j][0];
            hcfi[i][j] = out[i*N+j][1];
        }
    }
    
    if (loop > 0)
		Cprev = C[loop-1];
    
    /* Crank-Nicolson */
    #pragma omp parallel for //seulement pour les grands systèmes
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            hdtfr[i][j]=(hfr[i][j]*(1+dt*Cprev/2-dt*q2[i][j]/2)-dt*hcfr[i][j])/integ_coef[i][j];
            hdtfi[i][j]=(hfi[i][j]*(1+dt*Cprev/2-dt*q2[i][j]/2)-dt*hcfi[i][j])/integ_coef[i][j];
        }
    }

    /*INVERSE FFT*/
    #pragma omp parallel for //seulement pour les grands systèmes
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            in[i*N+j][0] = hdtfr[i][j];
            in[i*N+j][1] = hdtfi[i][j];
        }
    }
    fftw_execute(pb);
    #pragma omp parallel for //seulement pour les grands systèmes
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            h[i][j] = out[i*N+j][0]/(N*N);
        }
    }

    /* Measure Observables (instantaneous value) */
    if (loop >= (nloop/num_saves)*index_saves){
        Times[index_saves] = time;
        q2Ave[index_saves] = calcq2ave(hfr, hfi, q2, N);
    
        index_saves = index_saves + 1;
    }
    
}

tmax = time;
printf("\n Saving... tmax = %lf\n", tmax);

/*Save the final state and a slice of it*/
FILE* filefinalstate;

filefinalstate = fopen(state_dir, "w");
/*Save parameters N, tmax, dx, dt, seed, Ampl, Thalf*/
fprintf(filefinalstate, "%d %lf %lf\n", N, tmax, dx);
for (i=0; i<N; i++){
    for (j=0; j<N; j++){
        x = i*dx;
        y = j*dx;
        z = h[i][j];
        fprintf(filefinalstate, "%.20f %.20f %.20f\n", x, y, z);
    }
}
fclose(filefinalstate);

FILE* observables_file;
save_observable(observables_file, save_dir, "fileQ2.dat", Times, q2Ave, num_saves, 1);
return 0;
}
