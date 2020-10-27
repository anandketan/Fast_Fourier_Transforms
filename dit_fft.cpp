//DSP - DIT FFT 
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
    complex* DIT_FFT_reordered(complex input_seq[], int N);
    complex* DIT_FFT(complex input_seq[], int N, complex WN[], int recur_time_count);     

    complex* DIT_FFT_reordered(complex input_seq[], int N)                                                       
    {
        complex* reordered_seq = new complex[N];   //Initialize time sequence

        complex* WN = new complex[N];
        WN = Calc_WN(N);

        reordered_seq = reorder_seq(input_seq, N);

        reordered_seq = DIT_FFT(reordered_seq, N, WN, 0);

        return reordered_seq;   //Bit reversed sequence obtained - Decimated in time
    }

    complex* DIT_FFT(complex input_seq[], int N, complex WN[], int recur_time_count)
    {
        complex* return_seq = new complex[N];
        if (N != 2)
        {
            int k = pow(2,recur_time_count);
            complex* first_half_input_seq = new complex[N/2];
            complex* second_half_input_seq = new complex[N/2];
            for (int i = 0; i < N/2; ++i)
            {
                first_half_input_seq[i] = input_seq[i];
            }
            for (int i = 0; i < N/2; ++i)
        {
			second_half_input_seq[i] = input_seq[i+N/2];
		}

		complex* DFTed_first_half_seq = new complex[N/2];
		DFTed_first_half_seq = DIT_FFT(first_half_input_seq, N/2, WN, recur_time_count+1);
		complex* DFTed_second_half_seq = new complex[N/2];
		DFTed_second_half_seq = DIT_FFT(second_half_input_seq, N/2, WN, recur_time_count+1);

		complex* output_first_half_seq = new complex[N/2];
		complex* output_second_half_seq = new complex[N/2];

		for (int i = 0; i < N/2; ++i)
        {
			output_first_half_seq[i] = ComplexAdd(DFTed_first_half_seq[i], ComplexMul(DFTed_second_half_seq[i], WN[i*k]) ) ;
		}
        for (int i = 0; i < N/2; ++i)
        {
			output_second_half_seq[i] = ComplexAdd(DFTed_first_half_seq[i], ComplexMul(ReverseComplex(DFTed_second_half_seq[i]), WN[i*k]));
		}

		return_seq = append_seq(output_first_half_seq, output_second_half_seq, N/2);
		return return_seq;

        }
        else if ( N == 2 )   //Butterfly stage k-1 to handle 2 point FFT computation
        {
            return_seq[0] = ComplexAdd(input_seq[0], ComplexMul(input_seq[1], WN[0]));
            return_seq[1] = ComplexAdd(input_seq[0], ComplexMul( ReverseComplex(input_seq[1]), WN[0]));   //Final complex X(w) sequence FFT
            return return_seq;
        }
        return return_seq;
    }
}
