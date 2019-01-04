#include "input_output.h"

// get_N_Delta finds the number of points in the array between t1 and t2 evenly spaced by Delta
void get_N_Delta(int *N_Delta, double Delta, double t1, double t2) {

	int i = 0;
	double t = t1;
	while(t <= t2) {
		i++;
		t = t + Delta;
	}
	*N_Delta = i;

}

// get_N find the greater power of 2 less than the number of points in the
// array between t1 and t2 which is evenly spaced by Delta
void get_N(int *N, double Delta, double t1, double t2) {

	int j = 1;
	int i;

	get_N_Delta(&i, Delta, t1, t2);

	while(j <= i) {
		j = 2*j;
	}
	j = j/2;
	*N = j;

}


// get_t returns the t array with the number of elements given by N, a power of 2
void get_t(double *t, int N, double Delta, double t1, double t2) {

	double *t_Delta = NULL;
	int N_Delta, N_Delta_2;
	int i;
	int Ndiv2;

	get_N_Delta(&N_Delta, Delta, t1, t2);
	t_Delta = (double *) calloc(N_Delta, sizeof *t_Delta);
	for(i = 0; i < N_Delta; i++) {
		t_Delta[i] = t1 + i*Delta;
	}

	Ndiv2 = N/2;
	N_Delta_2 = ((int) ((((double) N_Delta)+1.0)/2.0)) - 1;
	for(i = 0; i < N; i++) {
		t[i] = t_Delta[N_Delta_2 - Ndiv2 + i];
	}

	free(t_Delta);
}

void sinc(double *h, double *t, int N) {

	int i, j;
	double pi = 3.14159;

	for(i = 0; i < 2*N; i += 2) {
		j = i/2;
		if(t[j] == 0.0) {
			h[i] = 1.0;
		}
		else {
			h[i] = sin(pi*t[j])/(pi*t[j]);
		}
	}

}

// get_f calculates the frequencies corresponding to the FFT
void get_f(double *f, int N, double Delta) {

	int i;
	double Ndiv2;
	double *n = NULL;

	Ndiv2 = N/2.0;

	n = (double *) calloc(N, sizeof *n);
	for(i = 0; i < N; i++) {
		n[i] = -Ndiv2 + i;
		f[i] = n[i]/(N*Delta);
	}

	free(n);

}


void print_array(double *d, int n, char s[]) {

	int i;
	FILE *fptr;

	fptr = fopen( s, "w" );

	for(i = 0; i < n; i++) {
		fprintf( fptr, "%.2f\n", d[i] ); 
	}

	fclose( fptr );

}