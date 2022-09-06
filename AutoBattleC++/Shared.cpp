#include "Shared.h"
#include <random>

using namespace std;

//used a more reliable number generator

int Shared::GetRandomInt(int min, int max)
{
	uniform_int_distribution<int> distribution(min, max);
	random_device rd;
	default_random_engine generator(rd());
	return distribution(generator);
}

