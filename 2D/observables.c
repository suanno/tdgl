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
