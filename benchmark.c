#include <stdio.h>
#include <time.h>
#include <string.h>
#include "include/fft.h"

void benchmark(complex_double_t *input,int N,char *argv[])
{
    complex_double_t sig_cpy[N];
    struct timespec start,end;

    if(strcmp(argv[2],"scalar") == 0)
    {
    	clock_gettime(CLOCK_MONOTONIC,&start);
		for(int iter=0;iter<100000;iter++)
		{
			memcpy(sig_cpy,input,sizeof(complex_double_t)*N);
			fft_scalar(sig_cpy,N);
		}
		clock_gettime(CLOCK_MONOTONIC,&end);
		double elapsed = (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/1e9;
		printf("Elapsed time: %lf sec\n",elapsed);
	}
	else if(strcmp(argv[2],"optimized") == 0)
	{
		clock_gettime(CLOCK_MONOTONIC,&start);
		for(int iter=0;iter<100000;iter++)
		{
			memcpy(sig_cpy,input,sizeof(complex_double_t)*N);
			fft_scalar_optimized(sig_cpy,N);
		}
		clock_gettime(CLOCK_MONOTONIC,&end);
		double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9;
		printf("Elapsed time: %lf sec\n",elapsed);
	}
}
