#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define D 1
#define pi 4*atan(1.0)

double calckink_dist(double* x, double* u, int N, double dx){		
    double central_plateau,x1,x2,u1,u2,xk,dist;
    int i = (int)(N/2);
	xk = 0; // (right) kink position
    central_plateau = u[i];
	while (i < N){
	    // Estimate the position of the zero x=xk (y0=0) with a linear fit
		// We store the value of y(=u) until it changes sign, so we can use the previous value to do the fit
		if (u[i]*central_plateau < 0){  //as soon as u<0 if the central plateau is >0; as soon as u>0 if the central plateau is <0 
			x1 = x2;
			x2 = (i-(int)(N/2))*dx;
			u1 = u2;
			u2 = u[i];
			xk = x1 + (u1/(u1-u2))*dx;
			//printf("%lf\n", u1*u2);
			dist = 2*xk;
            return dist;
		}
		x2 = (i-(int)(N/2))*dx;
		u2 = u[i];
		i = i + 1;
	}
    return 0;   //If it does not find any zero, it means that the kinks have a distance comparable with the dx
}

double calcq2ave(double* ufr, double* ufi, double* d2coef, int N, double dx){
	double weight_sum, q2ave;
    weight_sum = 0; q2ave = 0;
	for(int i=0; i<N; i++) {
	    /*Minus sign because the variable q2 is the observable -q2*/
		q2ave = q2ave - d2coef[i]*(ufr[i]*ufr[i] + ufi[i]*ufi[i]);
		weight_sum = weight_sum + (ufr[i]*ufr[i] + ufi[i]*ufi[i]);
	    //printf("u[%d][%d] = %.2lf\n", i, j, h[i][j]);
	}
	q2ave = q2ave/(weight_sum*D);
    return q2ave;
}

double calcelllDW(double* ufr, double* ufi, double* d2coef, int N, double dx){
    double grad2 = 0;
    for(int i=0;i<N;i++) {
        grad2 = grad2 - d2coef[i]*(ufr[i]*ufr[i] + ufi[i]*ufi[i])*(2*pi/(N*dx));
	}
	return (N*dx)/grad2;
}

int calcstructure_fact(double* ufr, double* ufi, int N, double* structure_fac){
	for (int i = 0; i < N; i++){
		structure_fac[i] = sqrt(ufr[i]*ufr[i]+ufi[i]*ufi[i]);
	}
	return 1;
}

int save_observable(FILE* dest_file, char* filename, double* obsx, double* obsy, int len, int append){
    double x, y;
	if (append == 1)
    	dest_file = fopen(filename, "a");
	else
    	dest_file = fopen(filename, "w");
    for (int i=0; i<len; i++){
        x = obsx[i];
        y = obsy[i];
        fprintf(dest_file, "%.5f %.20f\n", x, y);
    }
    fclose(dest_file);
    return 1;
}