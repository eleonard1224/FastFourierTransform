#ifndef _INPUT_FUNCTION_H_
#define _INPUT_FUNCTION_H_


#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void get_N_Delta(int *N_Delta, double Delta, double t1, double t2);

void get_N(int *N, double Delta, double t1, double t2);

void get_t(double *t, int N, double Delta, double t1, double t2);

void sinc(double *h, double *t, int N);

void get_f(double *f, int N, double Delta);

void print_array(double *d, int n, char s[]);

#endif