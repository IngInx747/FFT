#include "FFT.h"

#include <vector>
#include <cmath>

static constexpr float kPi4 = 0.7853981633974483f;
static constexpr float kPi2 = 1.5707963267948966f;
static constexpr float kPi = 3.141592653589793f;
static constexpr float k2Pi = 6.283185307179586f;

////////////////////////////////////////////////////////////////
// FFT
////////////////////////////////////////////////////////////////

// Unit circle element
inline Complex omega(int k, int n)
{
	return Complex(
		std::cosf(k2Pi * k / static_cast<float>(n)),
		std::sinf(k2Pi * k / static_cast<float>(n))
	);
}

// FFT
// Cooley-Tukey decimation-in-time radix-2
// In-space
void fft_1d_radix2(std::vector<Complex>& in, bool inverse = false)
{
	int n = in.size();

	// permute input array to FFT base level order
	for (int i = 0, j = 0; i < n; ++i)
	{
		if (i > j) std::swap(in[i], in[j]);

		for (int l = n >> 1; (j ^= l) < l; l >>= 1)
		{}
	}

	int way = 1; // forward
	if (inverse) way = -1; // backward

	// butterfly combination
	for (int l = 2; l <= n; l <<= 1)
	{
		int m = l / 2;

		for (int p = 0; p < n; p += l)
		{
			for (int i = 0; i < m; ++i)
			{
				Complex z = omega(n / l * i * way, n) * in[p + m + i];
				in[p + m + i] = in[p + i] - z;
				in[p + i] += z;
			}
		}
	}
}

// FFT 
// Bluestein's chirp z-transform
// In-space
void fft_1d_arbitrary(std::vector<Complex>& in)
{
	int n = in.size(), m;

	// expand array size to power-of-2 and simutaneously no less than 2N-1
	for (m = 1; m < n * 2 + 1; m <<= 1) {}

	std::vector<Complex>& seq_a = in;
	std::vector<Complex> seq_b(m);

	seq_a.resize(m);

	// construct two sequences
	for (int i = 0; i < n; ++i)
	{
		int k = (i * i) % (2 * n);
		seq_a[i] *= omega(-k, 2 * n);
	}

	for (int i = n; i < m; ++i)
	{
		seq_a[i] = 0;
	}

	for (int i = 0; i < n; ++i)
	{
		int k = (i * i) % (2 * n);
		seq_b[i] = omega(k, 2 * n);
	}

	for (int i = m - n; i < m; ++i)
	{
		int k = ((m - i) * (m - i)) % (2 * n);
		seq_b[i] = omega(k, 2 * n);
	}

	// convolution of two sequences 
	fft_1d_radix2(seq_a);
	fft_1d_radix2(seq_b);

	for (int i = 0; i < m; ++i)
	{
		seq_a[i] *= seq_b[i];
	}

	fft_1d_radix2(seq_a, true);
	float inv_m = 1.f / m;

	for (int i = 0; i < m; ++i)
	{
		seq_a[i] *= inv_m;
	}

	// mul phase shift to convolution result
	seq_a.resize(n);

	for (int i = 0; i < n; ++i)
	{
		int k = (i * i) % (2 * n);
		seq_a[i] *= omega(-k, 2 * n);
	}
}

// FFT entrance
void fft_1d(std::vector<Complex>& in)
{
	int n = in.size();

	// input size is power of 2
	if (n > 0 && (n & (n - 1)) == 0)
	{
		fft_1d_radix2(in);
	}

	// input size is arbitrary
	else
	{
		fft_1d_arbitrary(in);
	}
}
