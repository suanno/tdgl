//#include <iostream.h>
//#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include<math.h>
#include<stdlib.h>
#include<omp.h>

#define pi  4*atan(1.0)
#define num_obs 5

int main(int argc, char  *argv [ ]){

int i,j;

double L, dx, dt;
int N;
double u0;              /*Plateau value is +-u0*/
double r0;              /*Radius of the circular front*/
char* simul_name;           /*Name of the folder of savings*/


/* Read CMD parameters */
char *ptr;
int n_args = 4;         /*Number of required arguments*/
                        /*L, u0, simulation name*/
if (argc <= n_args){
    printf("Not enought input arguments");
    return 0;
}
L = strtod(argv[1], &ptr);
u0 = strtod(argv[2], &ptr);
r0 = strtod(argv[3], &ptr);
simul_name = argv[4];
if (r0 >= L/2){
    printf("WARNING: Radius of the circle is larger than L/2!!!\n");
}

/* Read parameters from params.txt */
FILE *fileparams;
fileparams = fopen("params.txt", "r");
fscanf(fileparams, "dx = %lf\ndt = %lf", &dx, &dt);
fclose(fileparams);

N = (int)(L/dx);
dx = (double)L/N;
printf("New dx = %lf\n", dx);

/* Prepare the save folder */
FILE* filestate;
FILE* fileinit;
char* save_dir = malloc(strlen(".saves")+1+strlen(simul_name));
strcpy(save_dir, ".saves/"); /* copy name into the new var */
strcat(save_dir, simul_name); /* add the extension */
mkdir(save_dir, 0700);
/* Prepare the initial state */
char* state_dir = malloc(strlen(save_dir)+1+strlen("state.dat"));
strcpy(state_dir, save_dir);
strcat(state_dir, "/state.dat");
filestate = fopen(state_dir, "w");
/*Backup the initial state (init.dat)*/
strcpy(state_dir, save_dir);
strcat(state_dir, "/init.dat");
fileinit = fopen(state_dir, "w");
/* Prepare the state */
double x, y, r;
fprintf(fileinit, "%d %lf %lf\n", N, 0.0, dx);
fprintf(filestate, "%d %lf %lf\n", N, 0.0, dx);
//#pragma omp parallel for  /*I want the x,y to be SORTED in the state.dat file. So no parallel!*/
for (i=0; i<N; i++){
    for (j=0; j<N; j++){
        x = i*dx;
        y = j*dx;
        /*Formula for a circular front*/
        r = sqrt((x-L/2)*(x-L/2)+(y-L/2)*(y-L/2));
        fprintf(filestate, "%.5f %.5f %.20f\n", x, y, -u0*tanh((r-r0)/sqrt(2)));
        fprintf(fileinit, "%.5f %.5f %.20f\n", x, y, -u0*tanh((r-r0)/sqrt(2)));
    }
}
printf("State prepared at: %s\n", state_dir);
free(state_dir);
fclose(fileinit);
fclose(filestate);
/* Copy parameters file */
char* params_dir = malloc(strlen(".saves")+1+strlen(simul_name)+1+strlen("params.txt"));
strcpy(params_dir, save_dir);
strcat(params_dir, "/params.txt");
fileinit = fopen(params_dir, "w");
fprintf(fileinit, "dx = %lf\ndt = %lf", dx, dt);
free(params_dir);

/* Prepare observable folders */
char observables[num_obs][20] = {"/fileQ2.dat", "/fileGrad2.dat", "/fileCout.dat", "/fileAveout.dat","/fileRadiout.dat"};
for (int i = 0; i < num_obs; i++){
    char* obs_dir = malloc(strlen(save_dir)+1+strlen(observables[i]));
    strcpy(obs_dir, save_dir);
    strcat(obs_dir, observables[i]);
    fileinit = fopen(obs_dir, "w");
    fclose(fileinit);
    free(obs_dir);
}
free(save_dir);


return 0;

}
