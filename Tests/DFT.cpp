/** This is a test of a discrete fourier transform algorithim
 * \author Henry J Schmale
 * \date 6 February 2015
 * Based on this article: http://practicalcryptography.com/miscellaneous/machine-learning/intuitive-guide-discrete-fourier-transform/
 */

#include <iostream>
#include <cmath>
#include <iomanip>

const double PI = 3.14159265;

template<typename TYP>
void pkdft(TYP *xt, TYP *pk, int n)
{
	TYP * iXk = new TYP[n];
	TYP * rXk = new TYP[n];

	// DFT
	for(int k = 0; k < n; k++)
	{
		iXk[k] = 0;
		rXk[k] = 0;
		for(int t = 0; t < n; t++)
		{
			iXk[k] += (xt[t] * std::cos((2 * PI * k * t) / n));
			rXk[k] += (xt[t] * std::sin((2 * PI * k * t) / n));
		}
	}

	// Calculate Power Spectrum
	for(int k = 0; k < n; k++)
	{
		pk[k] = (rXk[k] * rXk[k]) + (iXk[k] * iXk[k]);
	} 
	
	delete[] iXk;
	delete[] rXk;
}

int main()
{
	long double samps[100] = {1.000000, 0.616019, -0.074742, -0.867709, -1.513756, -1.814072, -1.695685, -1.238285, -0.641981, -0.148568, 0.052986, -0.099981, -0.519991, -1.004504, -1.316210, -1.277204, -0.840320, -0.109751, 0.697148, 1.332076, 1.610114, 1.479484, 1.039674, 0.500934, 0.100986, 0.011428, 0.270337, 0.767317, 1.286847, 1.593006, 1.522570, 1.050172, 0.300089, -0.500000, -1.105360, -1.347092, -1.195502, -0.769329, -0.287350, 0.018736, -0.003863, -0.368315, -0.942240, -1.498921, -1.805718, -1.715243, -1.223769, -0.474092, 0.298324, 0.855015, 1.045127, 0.861789, 0.442361, 0.012549, -0.203743, -0.073667, 0.391081, 1.037403, 1.629420, 1.939760, 1.838000, 1.341801, 0.610829, -0.114220, -0.603767, -0.726857, -0.500000, -0.078413, 0.306847, 0.441288, 0.212848, -0.342305, -1.051947, -1.673286, -1.986306, -1.878657, -1.389067, -0.692377, -0.032016, 0.373796, 0.415623, 0.133682, -0.299863, -0.650208, -0.713739, -0.399757, 0.231814, 0.991509, 1.632070, 1.942987, 1.831075, 1.355754, 0.705338, 0.123579, -0.184921, -0.133598, 0.213573, 0.668583, 0.994522, 1.000000};
	long double ret[100] = {0};

	pkdft(samps, ret, 100);

	// output data
	std::cout << "Index\tPower\tFreq" << std::endl;
	for(int i = 0; i < 100; i++)
	{
		std::cout << std::scientific << std::setprecision(5) << i << "\t" << ret[i] 
			  << "\t" << (i * 44100) / 100 << std::endl;
	}
	return 0;			
}
