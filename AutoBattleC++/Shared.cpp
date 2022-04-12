#include "Shared.h"

#include <cstdlib>
#include <ctime>

int Shared::GetRandomInt(int min, int max)
{
	srand(time(nullptr));
	return (rand() % max) + min;
}
