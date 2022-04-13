#include "Shared.h"

#include <cstdlib>
#include <ctime>
#include <random>

int Shared::GetRandomInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	std::random_device rd;
	std::default_random_engine generator(rd());
	return distribution(generator);

}
