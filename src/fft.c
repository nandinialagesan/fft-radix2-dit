#include <stdio.h>
#include "../include/fft.h"

complex_double_t compute_twiddle_factor(int k,int N)
{   
    //Calculate the Twiddle Factor
	complex_double_t Wk;
	Wk.real = cos((-2*M_PI*k)/N);
	Wk.imag = sin((-2*M_PI*k)/N);
	return Wk;
}

complex_double_t complex_multiplication(complex_double_t *a,complex_double_t *b)
{
	complex_double_t output;
	output.real = (a->real * b->real) - (a->imag * b->imag);
	output.imag = (a->real * b->imag) + (a->imag * b->real);
	return output;
}

complex_double_t complex_addition(complex_double_t *a,complex_double_t *b)
{
	complex_double_t sum;
	sum.real = a->real + b->real;
	sum.imag = a->imag + b->imag;
	return sum;
}

complex_double_t complex_subtract(complex_double_t *a, complex_double_t *b)
{
	complex_double_t diff;
	diff.real = a->real - b->real;
	diff.imag = a->imag - b->imag;
	return diff;
}

void bit_reverse(complex_double_t *input,int N)
{
	int bits = log2(N);
	for(int i=0;i<N;i++)
	{
	    int t = i, rev =0;
	    for(int j=0;j<bits;j++)
	    {
	    	rev = (rev<<1) | (t&1);
	    	t = t>>1;
	    }
		if(i<rev)
		{
			complex_double_t temp;
			temp = input[i];
			input[i] = input[rev];
			input[rev] = temp;
		}
	}

}

void fft_scalar(complex_double_t *input,int N)
{
    if((N & (N-1))!= 0)
    {
    	fprintf(stderr,"Error: N must be a power of 2\n");
    	return;
    }

	bit_reverse(input,N);
	
	for(int len=2;len<=N;len=len<<1)
	{
		int half_len = len>>1;
		for(int i=0;i<N;i+=len)
		{
			for(int k=0;k<half_len;k++)
			{ 
			   
				complex_double_t Wk = compute_twiddle_factor(k,len);
				complex_double_t even = input[i+k];
				complex_double_t odd = input[i+k+half_len];
				complex_double_t t   = complex_multiplication(&odd,&Wk);
				input[i+k] = complex_addition(&even,&t);
				input[i+k+half_len] = complex_subtract(&even,&t);
			}
		}
		
	}
}
