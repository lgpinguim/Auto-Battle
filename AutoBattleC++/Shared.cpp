#include "Shared.h"

#include <cstdlib>

int Shared::GetRandomInt(int min, int max)
{
	const int index = (rand() % max) + min;
	return index;
}
