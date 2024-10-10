// Solve the TDGL equation
// Forward integration using implicit Euler scheme
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#define D 1 //Dimension of the problem

#define pi 4*atan(1.0)

int main(int argc, char  *argv [ ]){

/*Parameters: They are read from previous simulation .dat file*/

int N=1000;
double dx=0.1;

double dt=0.01;
double tmin=1;	//tmin is the tmax of previous evolution
double Deltat = 10;
double tmax = tmin + Deltat;

/*C(t) = Cave + Ampl*sin(2pi*t)*/
double Cave = 0;
double Ampl = 1;
double Thalf = -1;  // T/2 If T < 0 it means C(t) = Cave costant
int notsmoothC = 0;	// 1: C(t) starts from 0 at the beginning of CURRENT/LAST evolution
					// 0: C(t) starts from zero at the beginning of the FISRT EVER evolution


/* Read parameters from last simulation */
FILE *fileinit;
int seed;
fileinit = fopen("tdgl_result.dat", "r");
/*First line is for parameters and seed
  tdgl adopts THE SAME parameters (N,dx, dt) that were used in the
  previous evolution with tdglfd or tdgl, unless specified in the command prompt.
*/
fscanf(fileinit, "%d %lf %lf %lf %d %lf %lf %lf\n", &N, &tmin, &dx, &dt, &seed, &Ampl, &Thalf, &Cave);
fclose(fileinit);

/* Get inputs from the terminal */
char *ptr;
char* fileCname;
int doreadCfromfile = 0;
//printf("argv1 = %lf", atof(argv[1]));
if (argc > 1)
	Deltat = strtod(argv[1], &ptr);
if (argc > 2){
  	Ampl = strtod(argv[2], &ptr);
	if (argc > 3){
		/*Period of the sine*/
		Thalf = strtod(argv[3], &ptr)/2;
		if (argc > 4){
		/*Offset of C(t)*/
		Cave = strtod(argv[4], &ptr);
		}
		if (argc > 5){
			/*Decide wether C(t) must vary SMOOTHLY between
			an evolution and the next one. Or if it shall start from
			sin(0) = 0 in the CURRENT/LAST evolution*/
			if (strtod(argv[5], &ptr) == 1)
				notsmoothC = 1;
		}
		if (argc > 6){
			/*Period of the sine*/
			dt = strtod(argv[6], &ptr);
		}
	}
	else{
		doreadCfromfile = 1;
		fileCname = argv[2];
	}
	printf("dt = %lf\n", dt);
}



/*The evolutions are consecutive, so the initial time (and state)
 are the finals of the previous evolution
*/
tmax = tmin + Deltat;
double ttime=0;
int nloop=(Deltat)/dt;
int loop;

double* x = malloc(N*sizeof(double));
double* u = malloc(N*sizeof(double));
double* uxx = malloc(N*sizeof(double));
double* ufr = malloc(N*sizeof(double));
double* ufi = malloc(N*sizeof(double));
double* udt = malloc(N*sizeof(double));
double* udtfr = malloc(N*sizeof(double));
double* udtfi = malloc(N*sizeof(double));

double* NL = malloc(N*sizeof(double));
double* NLfr = malloc(N*sizeof(double));
double* NLfi = malloc(N*sizeof(double));

int i;
double decainx=0;
double decainu=0;
double decaoutx=0;
double decaoutu=0;
double decaoutC=0;
double decaoutAve=0;
double decainC=0;
double decatime=0;

double* ffr = malloc(N*sizeof(double));
double* qfr = malloc(N*sizeof(double));
double* d2coef = malloc(N*sizeof(double));
double* integ_coef = malloc(N*sizeof(double));

FILE *stateeqn_result;
FILE *fileCout;				/*C(t+dt) values*/
FILE *fileAveout;			/*Space average of u(t) values*/
FILE *fileq2Aveout;			/*Space average of u(t) values*/
FILE *fileCin;
FILE *filex0;
FILE *fileumax;

double* C = malloc(nloop*sizeof(double));				/*C(t+dt) values*/
double Cprev;
//double* x0 = malloc(nloop*sizeof(double));	/*Interface position (where u=0)*/
double* umax = malloc(nloop*sizeof(double));
double weight_sum = 0;

/*Read C(t) from file*/
/*If the file is shorter than nloop, C(t)
is elonged Periodically*/
if (doreadCfromfile == 1){
	fileCin = fopen(fileCname, "r");
	loop = 0;
	while (loop < nloop){
		if(fscanf(fileCin, "%lf %lf \n", &decatime, &decainC) == EOF){
			fclose(fileCin);
			fileCin = fopen(fileCname, "r");
			fscanf(fileCin, "%lf %lf \n", &decatime, &decainC);
		}
		C[loop]=decainC;
		//printf("C[%d] = %lf\n", loop, C[loop]);
		loop = loop + 1;
	}
	fclose(fileCin);
}else{
	/*Define value of C(t) in time.
		C(t) = Cave + Ampl*sin(pi*t/(T/2))
		NOTE: Time "t" starts at the beginning of the FIRST of
		the serie of consecutive evolutions, and NOT at the beginning
		of the current simulation.
		So the C value at the beginning of the current simulation
		is NOT Ampl*sin(0) = 0 .
		BUT defining C(t) like this, we have the property that C(t)
		is varying SMOOTHLY during the WHOLE (total serie of consecutive evolutions) experiment.
	*/
	/*NOTE: As to calculate u(t+dt) we need C(t+dt), we adopt the following convention
		C[loop] = C(dt*loop + dt)
		So C[0] = C(0 + dt) and so on
	*/
	/*Define Cprev (C(t=0))*/
	if(Thalf > 0)
		Cprev = Cave + Ampl*sin(pi*(tmin*notsmoothC)/Thalf);
	else
		Cprev = Cave;

	for (loop=0;loop<nloop;loop++){
	ttime = tmin + (loop + 1)*dt;		/*C[loop] = C(t+dt), so it's NOT C(t)*/
	if(Thalf > 0){
		C[loop]=Cave + Ampl*sin(pi*(ttime-tmin*notsmoothC)/Thalf);
		}
		else							/*Thalf < 0 means you want to keep C = Cave + Ampl costant*/
			C[loop] = Cave;
	}
}

/*Define observables to track in time*/
int num_saves = 1000; /*Save the observable only at num_saves equispaced instants*/
if (nloop < num_saves)
    num_saves = nloop;
int index_saves = 0;
double* Times = malloc(num_saves*sizeof(double)); /*Times of saves*/
double* uAve = malloc(num_saves*sizeof(double));			/*Space average of u(t) values*/
double* q2Ave = malloc(num_saves*sizeof(double));
double* grad2 = malloc(num_saves*sizeof(double));
double* kik_dist = malloc(num_saves*sizeof(double));
int found_kink = 0;

ttime=0;
loop=0;

char filename[16];

/* TUNG: create plan for FFT*/
fftw_complex *in, *out;
fftw_plan pf,pb;
   
in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
pf = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
pb = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

/*Define q-space lattice*/
for (i=1; i<(N/2); i++){
ffr[i]=i;
ffr[N-i]=-i;
}
ffr[0]=0;
ffr[N/2]=N/2;	/*N MUST BE EVEN!!!*/
for (i=0; i<N; i++){
qfr[i]=ffr[i]*2*pi/N;
}

/*LOAD INITIAL STATE*/

FILE *fileinit2;
fileinit2 = fopen("tdgl_result.dat", "r");
/*First line is for parameters and seed*/
double Thalf_temp, dt_temp, Cave_temp, Ampl_temp;
fscanf(fileinit2, "%d %lf %lf %lf %d %lf %lf %lf\n", &N, &tmin, &dx, &dt_temp, &seed, &Ampl_temp, &Thalf_temp, &Cave_temp);
/*Now read the initial (smooth) state*/
for (i=0; i<N; i++){
fscanf(fileinit2, "%lf %lf\n", &decainx, &decainu);
x[i]=decainx;
u[i]=decainu;
/*printf("\n\n%lf\n", decainx);*/
}
fclose(fileinit2);

//------------------------------------

// coefficients for spectral derivatives (-q^2) array (with already the minus sign!)
for (i=0; i<N; i++){
d2coef[i]=-(qfr[i]/dx)*(qfr[i]/dx);
}

/* EVOLUTION CODE */
for (loop=0; loop < nloop; loop++){
	ttime = tmin + (loop+1)*dt;	/*We calculate u(t+dt) in this loop, 
	so the first time we calculate (and save in the .dat) u(tmin + dt), NOT u(t)*/

	/*Denominator of Crank-Nicolson*/
	for (i=0; i<N; i++){
	integ_coef[i]=1-dt*C[loop]/2-dt*d2coef[i]/2; 	//Note that d2coeff = -q^2 (already contains a minus sign)
											 		//And that C[loop] is C(t+dt), NOT C(t)
													//And the 1/2 is for Crank-Nicolson
	}

	/*Compute FFT of u(x)->U(q)*/
	for(i=0; i<N; i++) {
	in[i][0]=u[i];
	in[i][1]=0.0;
	}
	fftw_execute(pf); // repeat as needed
	for(i=0; i<N; i++) {
	ufr[i]=out[i][0];
	ufi[i]=out[i][1];
	}

	/*Compute FFT of u(x)^3 (u^3 is called NL: Non Linear term)*/
	for (i=0; i<N; i++){
	NL[i]=u[i]*u[i]*u[i];
	}

	for(i=0; i<N; i++) {
	in[i][0]=NL[i];
	in[i][1]=0.0;
	}
	fftw_execute(pf); // repeat as needed
	for(i=0; i<N; i++) {
	NLfr[i]=out[i][0];
	NLfi[i]=out[i][1];
	}

	/*C[loop] = C(t+dt) but we need even C(t)=Cprev*/
	if (loop > 0)
		Cprev = C[loop-1];
	
	/*Explicit euler*/
	for (i=0; i<N; i++){
		udtfr[i]=(ufr[i]*(Cprev+d2coef[i])-NLfr[i])*dt+ufr[i];
		udtfi[i]=(ufi[i]*(Cprev+d2coef[i])-NLfi[i])*dt+ufi[i];	
	}

	/*INVERSE FFT*/
	for(i=0; i<N; i++) {
	in[i][0]=udtfr[i];
	in[i][1]=udtfi[i];
	}
	fftw_execute(pb); // repeat as needed
	for(i=0; i<N; i++) {
	udt[i]=out[i][0]/N;
	}

	for(i=0; i<N; i++) {
	u[i]=udt[i];
	}

	
	/*Measure observables*/
	if (loop >= (nloop/num_saves)*index_saves){
		Times[index_saves] = ttime;	

		/*1) Compute q2 average*/
		q2Ave[index_saves] = 0;
		weight_sum = 0;
		for(i=0;i<N;i++) {
			/*Minus sign because teh variable q2 is the observable -q2*/
			q2Ave[index_saves] = q2Ave[index_saves] - d2coef[i]*(ufr[i]*ufr[i] + ufi[i]*ufi[i]);
			weight_sum = weight_sum + (ufr[i]*ufr[i] + ufi[i]*ufi[i]);
			//printf("u[%d][%d] = %.2lf\n", i, j, h[i][j]);
		}
		q2Ave[index_saves] = q2Ave[index_saves]/(weight_sum*D);

		/*2) Compute uAve */
		uAve[index_saves] = 0;
		for(i=0;i<N;i++) {
			uAve[index_saves] = uAve[index_saves] + u[i];
		}
		uAve[index_saves] = uAve[index_saves]/N;

		/*3) Compute integral of grad^2*/
		for(i=0;i<N;i++) {
			grad2[index_saves] = grad2[index_saves] + (qfr[i]/dx)*(qfr[i]/dx)*(ufr[i]*ufr[i] + ufi[i]*ufi[i])*(2*pi/(N*dx));
		}
		grad2[index_saves] = (N*dx)/grad2[index_saves];

		/*4) Compute the distance between kinks (makes sense only if there are only 2 kinks AND the system is symmetric!)*/
		/*Compute the second space derivative (it is zero at the kinks positions)*/
		/*INVERSE FFT of -q2*F(u)*/
		for(i=0; i<N; i++) {
		in[i][0]=-(qfr[i]/dx)*(qfr[i]/dx)*udtfr[i];
		in[i][1]=-(qfr[i]/dx)*(qfr[i]/dx)*udtfi[i];
		}
		fftw_execute(pb); // repeat as needed
		for(i=0; i<N; i++) {
		uxx[i]=out[i][0]/N;
		}
		/*Look for the zeros*/
		kik_dist[index_saves] = 0;
		found_kink = 0;
		for (i=(int)(N/2); i < N; i++){
			if (uxx[i] > 0 && found_kink == 0){
				kik_dist[index_saves] = (i-(int)(N/2))*dx*2;
				found_kink = 1;
			}
		}


		index_saves = index_saves + 1;
	}
/*
	x0[loop] = -1;
	/*Compute the position of the interface (u = 0)
	for (i = (int)(0.25*N); i<(int)(0.75*N); i++){
		if (u[i]/u[(int)(0.25*N)] < 0 && x0[loop] < 0)
			x0[loop] = 0.5*(x[i]+x[i-1]);
	}
*/

}

/*Save the final state*/
stateeqn_result = fopen("tdgl_result.dat", "w");
/*Save parameters N, tmax, dx, dt, seed, Ampl, Thalf*/
fprintf(stateeqn_result, "%d %.10lf %.10lf %.10lf %d %lf %lf %lf\n", N, tmax, dx, dt, seed, Ampl, Thalf, Cave);
for (i=0; i<N; i++){
decaoutx=x[i];
decaoutu=u[i];
fprintf(stateeqn_result, "%.10f %.20f\n", decaoutx, decaoutu);
}
fclose(stateeqn_result);


/*Save the values taken by C(t) in time.
  They are appendend, so you save its values from t=0
*/
fileCout = fopen("fileCout.dat", "a");
for (loop=0; loop<nloop; loop++){
ttime = tmin + (loop+1)*dt;
decaoutC = C[loop];
/*printf("C[%d] = %lf\n", loop, C[loop]);*/
fprintf(fileCout, "%.5f %.20f\n", ttime, decaoutC);
}
fclose(fileCout);

fileq2Aveout = fopen("fileq2Aveout.dat", "a");
for (loop=0; loop<num_saves; loop++){
ttime = Times[loop];
decaoutAve = q2Ave[loop];
fprintf(fileq2Aveout, "%.5f %.20f\n", ttime, decaoutAve);
}
fclose(fileq2Aveout);

fileAveout = fopen("fileAveout.dat", "a");
for (loop=0; loop<num_saves; loop++){
ttime = Times[loop];
decaoutAve = uAve[loop];
fprintf(fileAveout, "%.5f %.20f\n", ttime, decaoutAve);
}
fclose(fileAveout);

fileAveout = fopen("filegrad2.dat", "a");
for (loop=0; loop<num_saves; loop++){
ttime = Times[loop];
decaoutAve = grad2[loop];
fprintf(fileAveout, "%.5f %.20f\n", ttime, decaoutAve);
}
fclose(fileAveout);

fileAveout = fopen("filekinkdist.dat", "a");
for (loop=0; loop<num_saves; loop++){
ttime = Times[loop];
decaoutAve = kik_dist[loop];
fprintf(fileAveout, "%.5f %.20f\n", ttime, decaoutAve);
}
fclose(fileAveout);



/*Save interface position x0 (where u=0)
filex0 = fopen("filex0.dat", "a");
for (loop=0; loop<nloop; loop++){
ttime = tmin + (loop+1)*dt;
decaoutAve = x0[loop];
fprintf(filex0, "%.5f %.20f\n", ttime, decaoutAve);
}
fclose(fileAveout);
*/


fftw_destroy_plan(pf);
fftw_destroy_plan(pb);
fftw_free(in);
fftw_free(out);

free(x);
free(u);
free(uxx);
free(ufr);
free(ufi);
free(udt);
free(udtfr);
free(udtfi);
free(NL);
free(NLfr);
free(NLfi);
free(C);
free(uAve);
free(ffr);
free(qfr);
free(d2coef);
free(integ_coef);

	return 0;
}

