#include "Grid.h"
#include "Battlefield.h"
#include "Types.h"
#include "Character.h"
#include <iostream>


#include "Shared.h"

using namespace std;

Battlefield::Battlefield()
= default;

Grid* Battlefield::CreateBattleField(int& Lines, int& Columns)
{
	const auto new_grid = new Grid(Lines, Columns);
	cout << "\nThe battlefield has been created\n";
	SetGrid(new_grid);
	number_of_possible_tiles = new_grid->x_length * new_grid->y_length;
	return new_grid;
}


void Battlefield::AlocatePlayer(Character* player)
{
	bool searching_valid_position = true;

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

void Battlefield::ValidateBattlefieldDimensions(int& lines, int& columns) const
{
	bool incorrect_input = true;

	while (incorrect_input)
	{
		cout << "\nPlease choose the map height: ";
		string height;
		getline(cin, height);

		cout << "Please choose the map width: ";
		string width;
		getline(cin, width);

		lines = atoi(height.c_str());
		columns = atoi(width.c_str());
		const bool is_valid_matrix_size = lines * columns >= 2;

		if (is_valid_matrix_size)
		{
			incorrect_input = false;
		}
		else
		{
			cout << "Wrong dimensions, please try again!\n";
		}
	}
}

void Battlefield::DrawBattlefield(const vector<Character*>& all_players) const
{
	int index = 0;

	for (int i = 0; i < this->grid->x_length; i++)
	{
		for (int j = 0; j < this->grid->y_length; j++)
		{
			const Types::GridBox current_grid = grid->grids[index]; 

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
