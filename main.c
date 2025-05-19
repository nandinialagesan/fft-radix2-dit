#include <stdio.h>
#include <string.h>
#include "include/fft.h"

int main(int argc,char *argv[])
{
    //Generate a test signal - complex sine wave
    int k = 10; //Frequency bin
    int N = 1024; //FFT length 
    complex_double_t sig[N];
    for(int n=0;n<N;n++)
    {
    	sig[n].real = cos((2*M_PI*k*n)/N);
    	sig[n].imag = sin((2*M_PI*k*n)/N);
    }
    
    if((strcmp(argv[1],"benchmark")) == 0)
    {
    	benchmark(sig,N,argv);
    }//Benchmark
	else if ((strcmp(argv[1],"fft_out")) == 0)
    {
        if((strcmp(argv[2],"scalar")) == 0)
        {
          fft_scalar(sig,N);	
        }
        else if((strcmp(argv[2],"optimized")) == 0)
        {
        	fft_scalar_optimized(sig,N);
        }
    }
    else
    {
    	fprintf(stderr,"Error\n");
    }

    //Output signal
    FILE *fptr;
    fptr = fopen("time_domain_signal.txt","w");
    for(int i=0;i<N;i++)
    {
    	fprintf(fptr,"%lf %lf\n",sig[i].real, sig[i].imag);
    }
    fclose(fptr);

	return 0;
}
