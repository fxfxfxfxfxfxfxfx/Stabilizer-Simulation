// Random Clifford-Group Quantum Circuit Generator
// by Scott Aaronson
// Last modified 12/8/2003

// Example usage:  randqc n100 T10000 c0.5 h0.2 p0.2 m0.1 > rand.chp
// Generates a quantum circuit with 100 qubits and 10000 gates, consisting of 50% CNOT,
// 20% Hadamard, 20% phase, and 10% measurement.  Each gate is applied to a uniformly random
// qubit (or pair of qubits in the CNOT case)



#include <stdio.h>
#include <stdlib.h>
#include <time.h>



long getrandom(int n)
{
	long r = (RAND_MAX*rand() + rand()) % n;
	r = (r + n) % n;
	return r;
}

int main(int argc, char **argv)

{

	long n = 1000;		// number of qubits
	long T = 200000;	// number of gates
	double c = 1.0f;	// portion of gates that are CNOT
	double h = 1.0f;	// Hadamard
	double p = 1.0f;	// phase
	double m = 1.0f;	// measurement
	double sum;
	double r;
	long a;
	long b;
	long i;

	srand(time(0));
	for (i = 1; i < argc; i++)
	{
		if ((argv[i][0]=='n')||(argv[i][0]=='N')) sscanf(argv[i]+1, "%ld", &n);
		if ((argv[i][0]=='t')||(argv[i][0]=='T')) sscanf(argv[i]+1, "%ld", &T);
		if ((argv[i][0]=='c')||(argv[i][0]=='C')) sscanf(argv[i]+1, "%lf", &c);
		if ((argv[i][0]=='h')||(argv[i][0]=='H')) sscanf(argv[i]+1, "%lf", &h);
		if ((argv[i][0]=='p')||(argv[i][0]=='P')) sscanf(argv[i]+1, "%lf", &p);
		if ((argv[i][0]=='m')||(argv[i][0]=='M')) sscanf(argv[i]+1, "%lf", &m);
	}
	sum = c+h+p+m;
	c /= sum;
	h /= sum;
	p /= sum;
	m /= sum;
	printf("Randomly-generated Clifford group quantum circuit");
	printf("\nn=%ld qubits, T=%ld gates", n, T);
	printf("\nInstruction mix: %lf%% CNOT, %lf%% Hadamard, %lf%% Phase, %lf%% Measurement\n#",
			100.0f*c, 100.0f*h, 100.0f*p, 100.0f*m);
	for (i = 0; i < T; i++)
	{
		r = (double)rand()/RAND_MAX;
		a = getrandom(n);
		b = a;
		while (b==a)
				b = getrandom(n);
		if (r < c) printf("\nc %ld %ld", a, b);
		else if (r < c+h) printf("\nh %ld", a);
		else if (r < c+h+p) printf("\np %ld", a);
		else printf("\nm %ld", a);
	}
	
	return 0;

}