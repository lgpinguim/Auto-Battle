#include "Grid.h"
#include "Battlefield.h"
#include "Types.h"
#include "Character.h"
#include <iostream>


#include "Shared.h"

using namespace std;

Battlefield::Battlefield() : grid(nullptr)
{
}

//removed Get player choice, there is no need to have that here, as I created a classto handle the game turns

//removed Create Player Character, there is no need to have that here, only the Character class
//should create new characters;

//removed Create Enemy Character, there is no need to have that here, only the Character class
//should create new characters;

//removed start turn, as I created a Turn handler for handling the flow of the game;

//removed start turn, as I created a Turn handler for handling the flow of the game;

//removed handle turn, as I created a Turn handler for handling the flow of the game;

//Removed get random int, as it was a malpractice 

Grid* Battlefield::CreateBattleField(int Lines, int Columns)
{
	const auto newGrid = new Grid(Lines, Columns);
	std::cout << "\nThe battlefield has been created\n";
	setGrid(newGrid);
	number_of_possible_tiles = newGrid->x_length * newGrid->y_length;
	return newGrid;
}


//Removed both Alocate player and enemy functions, created a generic alocate function
void Battlefield::AlocatePlayer(Character* player)
{
	Shared util;
	const int random = util.GetRandomInt(0, number_of_possible_tiles - 1);
	auto l_front = grid->grids.begin();
	advance(l_front, random);
	const Types::GridBox* RandomLocation = &*l_front;
	if (!RandomLocation->occupied)
	{
		index_location_of_each_player.push_back(l_front->index);
		l_front->occupied = true;
		player->current_box = *l_front;
	}
	else
	{
		AlocatePlayer(player);
	}
}


//This was the function from GRID, here it makes more sense.
//I also refactored the method so we can see the icon of each Character class.
void Battlefield::DrawBattlefield(std::vector<Character*> all_players)
{
	int index = 0;

	for (int i = 0; i < this->grid->x_length; i++)
	{
		for (int j = 0; j < this->grid->y_length; j++)
		{
			const Types::GridBox currentGrid = grid->grids[index]; //fixed typo on variable name

			if (currentGrid.occupied)
			{
				for (auto player : all_players)
				{
					if (player->current_box.index == currentGrid.index)
					{
						cout << "[" << player->icon << "]\t";
					}
				}
			}
			else
			{
				cout << "[ ]\t";
			}

			index++;
		}
		printf("\n");
	}
	printf("\n");
}
