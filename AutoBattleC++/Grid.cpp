#include "Grid.h"
#include "Types.h"


Grid::Grid(int lines, int columns) : x_length(lines), y_length(columns)
{
	//Organized the function for better readability and fixed possible errors.
	for (int i = 0; i < x_length; i++)
	{
		for (int j = 0; j < y_length; j++)
		{
			grids.emplace_back(j, i, (columns * i + j));
		}
	}
}

//modernized destructor.
Grid::~Grid()
= default;
