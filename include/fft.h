#ifndef FFT_H
#define FFT_H
#include <stdio.h>
#include <math.h>

typedef struct
{
	double real;
	double imag;
}complex_double_t;

void fft_scalar(complex_double_t *input,int N);
void fft_scalar_optimized(complex_double_t *input,int N);
void benchmark(complex_double_t *input,int N,char *argv[]);
#endif
