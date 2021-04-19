#pragma once
#include <random>

namespace RB
{
	// check out https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	class RandomInteger
	{
	public:
		/// <summary>
		/// including min and max
		/// </summary>
		int GetInteger(int min, int max)
		{
			std::random_device device;
			std::mt19937 generator(device());
			std::uniform_int_distribution<int> distribution(min, max);

			return distribution(generator);
		}
	};
}