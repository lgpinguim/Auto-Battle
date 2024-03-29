#pragma once
#include "Character.h"
#include <list>
#include "Grid.h"
#include "TurnHandler.h"


class Battlefield 
{
public:
	Battlefield();

	Grid* grid{};

	std::vector<int> index_location_of_each_player;

	int number_of_possible_tiles{};

	void SetGrid(Grid* g)
	{
		grid = g;
	}

	Grid* CreateBattleField(int& lines, int& columns);

	void AlocatePlayer(Character* player);

	void ValidateBattlefieldDimensions(int& lines, int& columns) const;

	void DrawBattlefield(const std::vector<Character*>& all_players) const;
};
