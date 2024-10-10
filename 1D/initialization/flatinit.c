//#include <iostream.h>
//#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<omp.h>
#include <time.h>

#define pi  4*atan(1.0)

//pour générer des nombres aléatoires
double randU(double randmin, double randmax)
{
double randU1=0.;
randU1 = randmin*(1-rand()/(double)RAND_MAX)+randmax*rand()/(double)RAND_MAX;
return randU1;
}

int main(int argc, char  *argv [ ]){

int i;

int N=1000;
double u0;              /*Initial flat value*/
int seed;
double hmoy = 0;


seed = time(NULL);
srand(seed);

char *ptr;
if (argc > 1)
	N = (int)strtod(argv[1], &ptr);
if (argc > 2){
  	u0 = strtod(argv[2], &ptr);
} else{
    u0=randU(1, 1)+hmoy;
}

double dx, dt, Ampl, Thalf, Cave;
FILE *fileparams;
fileparams = fopen("parameters.dat", "r");
fscanf(fileparams, "dx %lf\ndt %lf\nA %lf\nT %lf\nCave %lf", &dx, &dt, &Ampl, &Thalf, &Cave);
fclose(fileparams);

FILE *fileinit;

double decau, decax;
fileinit = fopen("tdgl_result.dat", "w");
fprintf(fileinit, "%d %.10lf %.10lf %.10lf %d %lf %lf %lf\n", N, 0, dx, dt, seed, 0, -1, 1);
#pragma omp parallel for
for(i=0;i<N;i++) {
    decax=i*dx;
    decau = u0;
    fprintf(fileinit, "%.5f %.20f\n", decax, decau);
}
fclose(fileinit);

/*Recreate fileCout of values of C(t) [Progressive
executions of the dynamics will APPEND info]*/
FILE *file;
file = fopen("fileCout.dat", "w");
fclose(file);
file = fopen("fileAveout.dat", "w");
fclose(file);
file = fopen("fileq2Aveout.dat", "w");
fclose(file);


return 0;

}
