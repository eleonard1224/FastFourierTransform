#include "fft.h"
#include "input_output.h"


// Fast Fourier Transform - Input h(t) and return H(f) 

int main() {


	double Delta; // Delta is the time interval between time samples 
	double t1, t2; // t1, t2 are the time endpoints in the array which is evenly spaced by Delta
	int N; // N will be the number of complex data points and will be a power of 2
	double *t = NULL;
	double *f = NULL;
	double *h = NULL;
	char st[] = "t";
	char sh[] = "ht";
	char sH[] = "Hf";
	char sf[] = "f";

	Delta = 0.01;
	t1 = -35.0; t2 = 35.0;

	get_N(&N, Delta, t1, t2);
	t = (double *) calloc(N, sizeof *t);
	get_t(t, N, Delta, t1, t2);
	print_array(t, N, st);

	f = (double *) calloc(N, sizeof *f);
	get_f(f, N, Delta);
	print_array(f, N, sf);

	h = (double *) calloc(2*N, sizeof *t);
	sinc(h, t, N);
	print_array(h, 2*N, sh);
	bit_reversal(h, N);
	fft(h, N, Delta);
	print_array(h, 2*N, sH);

	free(t);
	free(f);
	free(h);
	return 0;

}



