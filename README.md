# Fast Fourier Transform (FFT) Algorithms

Implementation of the Decimation in Time (DIT) and Decimation in Frequency (DIF) Fast Fourier Transforms to improve computational efficiency of signal conversion from time domain to frequency domain. The intuitive idea behind the FFT is to divide the original signal into two smaller signals, compute their DFTs and rejoin them to get the DFT of the original signal. The increase in efficiency is clear due to reduction in order of complexity from n^2 to n*log(n).

## Twiddle Factor

Each stage of the FFT butterfly (see figure) is multiplied with an exponential co-efficient that increases by an order (k) depending on the number of points (N) which have the relation N = 2^k. The code in this project written for an N = 8 (= 2^3) point FFT algorithm, hence k goes upto 3. 

More about the twiddle factor here: https://en.wikipedia.org/wiki/Twiddle_factor

## Concept of Decimation

The radix-2 DIT algorithm rearranges the discrete Fourier transform equation into two parts: a sum over the even-numbered discrete-time indices n = [0,2,4,…,N−2] and a sum over the odd-numbered indices n = [1,3,5,…,N−1] hence breaking down in time domain. the reverse is done to obtain a DIF series depending on application.

## References
Spectral analysis: https://cnx.org/contents/0sbTkzWQ@2.2:zmcmahhR@7/Decimation-in-time-DIT-Radix-2-FFT <br>
Frequency decimation: https://www.researchgate.net/figure/point-radix-2-DIF-FFT_fig8_299520102 <br>
FPGA implementation of FFT: https://www.semanticscholar.org/paper/Simple-Computation-of-DIT-FFT 
