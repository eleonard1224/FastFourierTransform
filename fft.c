#include "fft.h"

void fft(double *h, int N, double Delta) {

	// Now that f has been bit-reversed, can perform 
	// the Danielson-Lanczos algorithm 

	int n, NN, m, i, j, k;
	double theta, alpha, beta, wr, wi, tempr, tempi, wrtemp, witemp;
	double temp1, temp2;
	double pi = 3.14159;

	NN = 2*N;
	n = 2; // Going to perform the two-point transforms first

	while( n < NN ) { // 2-point transforms, 4-point transforms, etc.
		theta = 2*pi/n; // theta is in the exponent for W_n
		alpha = 2*sin(theta/2)*sin(theta/2); beta = sin(theta); // for powers of W_n
		wr = 1.0; wi = 0.0;
		m = 2*n;
		for( k = 0; k < n; k += 2) {
			for( i = k; i < NN; i += m ) {
				j = i + n;
				tempr = wr*h[j]-wi*h[j+1];
				tempi = wr*h[j+1]+wi*h[j];
				h[j] = h[i]-tempr;
				h[j+1] = h[i+1]-tempi;
				h[i] = h[i] + tempr;
				h[i+1] = h[i+1] + tempi;
			}  
			wrtemp = wr - (alpha*wr + beta*wi);
			witemp = wi - (alpha*wi - beta*wr);
			wr = wrtemp; wi = witemp;
		}
		n = 2*n;
	}

	// Going to get h in the right order for plotting
	for( i = 0; i < N; i += 2) {
		j = i + N;
		swap(h, i, j); 
	}

	// Multiplying by Delta
	for(i = 0; i < NN; i++) {
		h[i] = Delta*h[i];
	}

}

void swap(double *d, int i, int j) {

	double tempr, tempi;


	tempr = d[j];
	tempi = d[j+1];
	d[j] = d[i];
	d[j+1] = d[i+1];
	d[i] = tempr;
	d[i+1] = tempi;

}

// N must be a power of 2
void bit_reversal(double *d, int N) {

	int i, j, m, NN;

	NN = 2*N;
	j = 0;
	for(i = 0; i < NN; i += 2) {
		if(j > i) {
			swap(d,i,j);
		}

		m = N;
		while((m >= 2) && (j > (m-1))) {
			j = j - m;
			m = m/2;
		}
		j = j + m;
	}
}