#include <stdio.h>
#include <immintrin.h>
#include "../include/fft.h"
#include "../include/fft_lut.h"

void bit_reverse_opt1(double *re,double *imag,int N)
{
	for(int i=0;i<N;i++)
	{
		if(i<reverse_bits_lut[i])
		{
		    double temp_re,temp_imag;
			temp_re = re[i];
			re[i] = re[reverse_bits_lut[i]];
			re[reverse_bits_lut[i]] = temp_re;

			temp_imag = imag[i];
			imag[i] = imag[reverse_bits_lut[i]];
			imag[reverse_bits_lut[i]] = temp_imag;
		}
	}

}

void fft_avx(double *re,double *imag,int N)
{
    if((N & (N-1))!= 0)
    {
    	fprintf(stderr,"Error: N must be a power of 2\n");
    	return;
    }

	bit_reverse_opt1(re,imag,N);

	for(int len=2;len<=N;len = len<<1)
	{
		int half_len = len>>1;
		int index = N/len;
		for(int i=0;i<N;i+=len)
		{   
			for(int k=0;k<half_len;k+4)
			{
			    int twiddle_index = k * index;
				complex_double_t Wk,t;

				
				Wk.real = twiddle_factor_lut_real[twiddle_index];
				Wk.imag = twiddle_factor_lut_imag[twiddle_index];
				complex_double_t even = input[i+k];
				complex_double_t odd = input[i+k+half_len];
				t.real = odd.real * Wk.real - odd.imag * Wk.imag;
				t.imag = odd.real * Wk.imag + odd.imag * Wk.real;
				input[i+k].real = even.real + t.real;
				input[i+k].imag = even.imag + t.imag;
				input[i+k+half_len].real = even.real - t.real;
				input[i+k+half_len].imag = even.imag - t.imag;
			}
		}
		
	}
	
}
