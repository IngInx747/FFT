#include "Complex.h"
#include "FFT.h"

#include <ctime>
#include <random>

using namespace std;

inline double When()
{
#ifndef _WIN32
	static struct timeval tp;
	gettimeofday(&tp, NULL);
	double t = (double)tp.tv_sec;
	double t1 = (double)tp.tv_usec;
	return (t + t1 * 1e-6);
#else
	clock_t start = clock();
	double duration = (double)start / CLOCKS_PER_SEC;
	return duration;
#endif
}

int test_my_fft()
{
	double t0;
	int NumImg = 100000;
	int Nx = (1 << 3) + 10;
	vector<Complex> x(Nx), z(Nx);
	float scale = (float)(Nx);

	for (int j = 0; j < Nx; ++j)
	{
		float val = (j % 4 + j * j % 8);
		x[j].re = val;
		x[j].im = 0.f;
		printf("T(%d) = %f\n", j, val);
	}

	t0 = When();
	for (int loop = 0; loop < NumImg; ++loop)
	{
		std::copy(x.begin(), x.end(), z.begin());
		fft_1d(z);
	}
	printf("[My in-space 1D FFT] time = %lfsec\n", When() - t0);

	for (int i = 0; i < Nx; ++i)
	{
		printf("F(%d) = (%f, %f)\n", i, z[i].real(), z[i].imag());
	}

	return 0;
}

int main()
{
	test_my_fft();

	return 0;
}