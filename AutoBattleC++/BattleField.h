#pragma once
#include "Character.h"
#include <list>
#include "Grid.h"
#include "TurnHandler.h"

//Removed the namespace reference, using it in the header file could cause problems, it is a good practice to avoid this.
class Battlefield //fixed typo on name
{
public:

	Battlefield();

	// fixed naming conventions on the properties of this class.
	Grid* grid{};

	//Removed the the variables that represent the player and enemy location

	//A vector that will store the index location of each player.
	std::vector<int> index_location_of_each_player;

	//there is no need to have a pointer to each player when we have a list of all players that we could iterate as needed.
	// removed number of turns from battlefield.
	int number_of_possible_tiles{};

	//removed the turn handling from battlefield, so we can follow clean code practices 

	//removed creation of characters from battlefield class.

	//Removed class that violated clean code standards

	//Added Function for battlefield creation

	void setGrid(Grid* g)
	{
		grid = g;
	}

	Grid* CreateBattleField(int Lines, int Columns);

	//We should have only one function for player alocation.
	void AlocatePlayer(Character* player);

	void DrawBattlefield(std::vector<Character*> all_players);
};


