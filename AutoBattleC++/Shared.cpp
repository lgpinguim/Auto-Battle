#include "Shared.h"

#include <cstdlib>

int Shared::GetRandomInt(int min, int max)
{
	return (rand() % max) + min;
}
