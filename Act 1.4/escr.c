#include <stdio.h>
#include <math.h>
#include <omp.h>

#define NUM_THREADS 6
   FILE *fptr;
int main()
{
   long N = 6000000;
   const double startTime = omp_get_wtime();
   fptr=fopen("Euler_n_0.txt","w");
   printf("Numero de pasos:%d Atendido por thread:%d\n", N,omp_set_num_threads(NUM_THREADS));
 	 fprintf(fptr, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
       double h,t,w,ab;
       double w0=0.5,a=0,b=2;
       int i;
       w=w0;
       fprintf(fptr, "%f\t %f\n", a, w);
       for(i=0;i<N;i++){
           h=(b-a)/N;
           t=a+(h*i);
           ab=t*t;
           w=w+h*(1+pow(t-w,2));
           fprintf(fptr, "%f\t %f \t numero de thread:%d\n", t+h, w,omp_get_thread_num());
          }
          const double endTime = omp_get_wtime();
         printf("tomo (%lf) segundos\n", (endTime - startTime));
   fclose(fptr);
}