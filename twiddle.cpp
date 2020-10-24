//Twiddle computation
//The factor is defined as WN = e^(k*n)
//Hence depends on N-value, number of points

//******************************************************************

# include <iostream>
# include <stdlib.h>
# include <cmath>
# include <ctime>
# define PI 3.1415926
using namespace std;

typedef struct Complex
{
	double re;
	double im;
	Complex()
	{
		re = 0;
		im = 0;
	};
	Complex(double a,double b)
	{
		re = a;
		im = b;
	};
} complex;

complex* append_seq(complex seq_1[], complex seq_2[], int N);
complex* reorder_seq(complex input_seq[], int N);
complex* Calc_WN(int N);
int reverse_bit(int value, int N);

complex ComplexMul(complex c1, complex c2)   //Multiplier setup
{
	complex r;

	r.re = c1.re*c2.re - c1.im*c2.im;
	r.im = c1.re*c2.im + c1.im*c2.re;

	return r;
}

complex ComplexAdd(complex c1, complex c2)   //Adder setup
{
	complex r;

	r.re = c1.re + c2.re;
	r.im = c1.im + c2.im;

	return r;
}

complex ReverseComplex(complex c)   //Inverter setup
{
	c.re = -c.re;
	c.im = -c.im;

	return c;
}

complex* append_seq(complex seq_1[], complex seq_2[], int N)
{
	complex* total_seq = new complex[N*2];
	for (int i = 0; i < N; i++)
    {
		total_seq[i] = seq_1[i];
	}
	for (int i = N; i < 2*N; i++)
	{
		total_seq[i] = seq_2[i-N];
	}
	return total_seq;   // Append [seq_1] & [seq_2] to [seq_1,seq_2]
}

complex* reorder_seq(complex input_seq[], int N)
{
    cout << "Reorder the sequence = ";

	complex* reordered_seq = new complex[N];
	for (int i = 0; i < N; ++i)
	{
		int k = reverse_bit(i, log2(N));
		reordered_seq[k] = input_seq[i];
	}

	return reordered_seq;   // Reorder the input_seq to an order
}

int reverse_bit(int value, int N)
{
    int ret = 0;
	int i = 0;

	while (i < N)
    {
		ret <<= 1;
		ret |= (value>>i) & 1;
		i++;
	}

	return ret;  // N-based reverse method
}

complex* Calc_WN(int N)
{
    cout << "Calculating WN[] of N = " << N << "\t";
	complex* WN = new complex[N];

	complex WN_unit; WN_unit.re = cos(2*PI/N); WN_unit.im = -sin(2*PI/N);
	WN[0].re=1; WN[0].im=0;

	for (int i = 1; i < N; ++i)
	{
		WN[i] = ComplexMul(WN[i-1], WN_unit);
	}

	return WN;   // Calc WN[], with N = input_N
}

