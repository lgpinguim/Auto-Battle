#include "Grid.h"
#include "Battlefield.h"
#include "Types.h"
#include "Character.h"
#include <iostream>


#include "Shared.h"

using namespace std;

Battlefield::Battlefield()
= default;

//removed Get player choice, there is no need to have that here, as I created a class to handle the game turns

//removed Create Player Character, there is no need to have that here, only the Character class
//should create new characters;

//removed Create Enemy Character, there is no need to have that here, only the Character class
//should create new characters;

//removed start turn, as I created a Turn handler for handling the flow of the game;

//removed start turn, as I created a Turn handler for handling the flow of the game;

//removed handle turn, as I created a Turn handler for handling the flow of the game;

//Removed get random int, as it was a malpractice 

//function used to create the battlefield and store how many tiles we have
Grid* Battlefield::CreateBattleField(int& Lines, int& Columns)
{
	const auto new_grid = new Grid(Lines, Columns);
	cout << "\nThe battlefield has been created\n";
	setGrid(new_grid);
	number_of_possible_tiles = new_grid->x_length * new_grid->y_length;
	return new_grid;
}


//Removed both alocate player and enemy functions, created a generic alocate function
void Battlefield::AlocatePlayer(Character* player)
{
	bool searching_valid_position = true;
	//Improved performance and confiability using while instead of recursiveness.
	while (searching_valid_position)
	{
		const int random = Shared::GetRandomInt(0, number_of_possible_tiles - 1);
		auto l_front = grid->grids.begin();
		advance(l_front, random);
		const Types::GridBox* random_location = &*l_front;
		if (!random_location->occupied)
		{
			index_location_of_each_player.push_back(l_front->index);
			l_front->occupied = true;
			player->current_box = *l_front;
			searching_valid_position = false;
		}
	}
}


//a simple validator before we create the battlefield
void Battlefield::ValidateBattlefieldDimensions(int& lines, int& columns) const
{
	bool incorrect_input = true;

	while (incorrect_input)
	{
		//Building the map
		std::cout << "Please choose the map height: ";
		std::string height;
		getline(std::cin, height);

		std::cout << "Please choose the map width: ";
		std::string width;
		getline(std::cin, width);


		lines = atoi(height.c_str());
		columns = atoi(width.c_str());
		const bool is_valid_matrix_size = lines * columns >= 2;

		if (lines >= 2 && is_valid_matrix_size)
		{
			incorrect_input = false;
		}
		else
		{
			std::cout << "Wrong dimensions, please try again!\n";
		}
	}
}

//This was the function from GRID, here it makes more sense.
//I also refactored the method so we can see the icon of each Character class.
void Battlefield::DrawBattlefield(const std::vector<Character*>& all_players) const
{
	int index = 0;

	for (int i = 0; i < this->grid->x_length; i++)
	{
		for (int j = 0; j < this->grid->y_length; j++)
		{
			const Types::GridBox current_grid = grid->grids[index]; //fixed typo on variable name

			if (current_grid.occupied)
			{
				for (const auto player : all_players)
				{
					if (player->current_box.index == current_grid.index)
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
