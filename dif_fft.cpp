//DSP - DIF FFT
//List out 2^k points (real/complex) in: input_seq[]
//Twiddle computation: complex WN[]
//Capable of ultimately handling only Radix-2 DFT computation. N = power of 2

//******************************************************************

# include <iostream>
# include <complex.h>
# include <stdlib.h>
# include <cmath>
# include <ctime>
using namespace std;

int main()

{
    complex* DIF_FFT_reordered(complex input_seq[], int N);
    complex* DIF_FFT(complex input_seq[], int N, complex WN[], int recur_time_count)
    complex* DIF_FFT_reordered(complex input_seq[], int N)
    {
        complex* reordered_seq = new complex[N];   //Given sequence in time domain

        complex* WN = new complex[N];   //Compute twiddle factor
        WN = Calc_WN(N);

        reordered_seq = DIF_FFT(input_seq, N, WN, 0);   //Bit reversing for stage-2 decimation
        reordered_seq = reorder_seq(reordered_seq, N);

        return reordered_seq;
    }

        complex* DIF_FFT(complex input_seq[], int N, complex WN[], int recur_time_count)
        {
            complex* return_seq = new complex[N];

            if (N != 2)
                {
                    complex* first_half_seq = new complex[N/2];
                    complex* second_half_seq = new complex[N/2];

                    int k = pow(2,recur_time_count);
                    for (int i = 0; i < N/2; ++i)
                        {
                            first_half_seq[i] = ComplexAdd(input_seq[i], input_seq[i+N/2]) ;
                        }
                    for (int i = 0; i < N/2; ++i)
                    {
                        second_half_seq[i] = ComplexMul(ComplexAdd(input_seq[i], ReverseComplex(input_seq[i+N/2])), WN[i*k]) ;
                    }

                    complex* DFTed_first_half_seq = new complex[N/2];   //Discrete FT computation
                    DFTed_first_half_seq = DIF_FFT(first_half_seq, N/2, WN, recur_time_count+1);
                    complex* DFTed_second_half_seq = new complex[N/2];
                    DFTed_second_half_seq = DIF_FFT(second_half_seq, N/2, WN, recur_time_count+1)

                    return_seq = append_seq(DFTed_first_half_seq, DFTed_second_half_seq, N/2);   //Dimensional incompatibility
                    return return_seq;

                }
            else if (N == 2)   //Stage-3 calculate of Radix-2 DFT
                {
                    return_seq[0] = ComplexAdd(input_seq[0], input_seq[1]);
                    return_seq[1] = ComplexMul(ComplexAdd(input_seq[0], ReverseComplex(input_seq[1])), WN[0] );
                    return return_seq;
                }
	return return_seq;
    }
}
