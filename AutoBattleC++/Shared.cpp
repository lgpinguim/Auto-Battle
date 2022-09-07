#include "Shared.h"
#include <random>

using namespace std;

int Shared::GetRandomInt(int min, int max)
{
	uniform_int_distribution<int> distribution(min, max);
	random_device rd;
	default_random_engine generator(rd());
	return distribution(generator);
}

