#pragma once
#include <Vector>
#include "Types.h"

//standardized the code for properties, variable names and functions.

class Grid
{
public:
	//changed variable names to C++ standards
	Grid(int& lines, int& columns);

	std::vector<Types::GridBox> grids;

	int x_length; //fixed typo here
	int y_length;

};
