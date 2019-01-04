#ifndef _FFT_H_
#define _FFT_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void fft(double *h, int N, double Delta);
void swap(double *d, int i, int j);
void bit_reversal(double *d, int N);

#endif