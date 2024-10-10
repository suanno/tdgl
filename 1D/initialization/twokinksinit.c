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

double doublekink(double x, double x1, double x2, double C0){
    return sqrt(C0)*(tanh(sqrt(C0/2)*(x-x1))-tanh(sqrt(C0/2)*(x-x2))-1);
}

int main(int argc, char  *argv [ ]){
    int i;

    int N, seed;
    double L, u0, d;              /*Initial flat value*/

    seed = time(NULL);
    srand(seed);

    char *ptr;
    if (argc > 1){
        N = (int)strtod(argv[1], &ptr);
        u0 = 1;
        d = L/3;
    }
    if (argc > 2)
        d = strtod(argv[2], &ptr);
    if (argc > 2)
        u0 = strtod(argv[3], &ptr);

    FILE *file;
    FILE *file_init;
    double dx, dt, Ampl, Thalf, Cave;
    file = fopen("parameters.dat", "r");
    fscanf(file, "dx %lf\ndt %lf\nA %lf\nT %lf\nCave %lf", &dx, &dt, &Ampl, &Thalf, &Cave);
    fclose(file);
    
    L = N*dx;
    file = fopen("tdgl_result.dat", "w");
    file_init = fopen("fileinit.dat", "w");
    fprintf(file, "%d %.10lf %.10lf %.10lf %d %lf %lf %lf\n", N, 0., dx, dt, seed, Ampl, Thalf, Cave);
    double x;
    for (i=0; i<N; i++){
        x = i*dx;
        fprintf(file, "%.20f %.20f\n", x, doublekink(x, L/2-d/2, L/2+d/2, u0*u0));
        fprintf(file_init, "%.20f\n", doublekink(x, L/2-d/2, L/2+d/2, u0*u0));
    }

    fclose(file);
    fclose(file_init);
    /*Recreate fileCout of values of C(t) [Progressive
    executions of the dynamics will APPEND info]*/
    file = fopen("fileCout.dat", "w");
    fclose(file);
    file = fopen("fileAveout.dat", "w");
    fclose(file);
    file = fopen("filegrad2.dat", "w");
    fclose(file);
    file = fopen("fileq2Aveout.dat", "w");
    fclose(file);
    file = fopen("filekinkdist.dat", "w");
    fclose(file);

return 0;
}
