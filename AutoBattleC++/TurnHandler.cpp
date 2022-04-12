#include "TurnHandler.h"

#include <iostream>

#include "Battlefield.h"
#include "Shared.h"


TurnHandler::TurnHandler()
= default;

//modernized the destructor class.
TurnHandler::~TurnHandler()
= default;

void TurnHandler::ValidateBattlefieldDimensions(int& lines, int& columns) const
{
	bool incorrectInput = true;

	while (incorrectInput)
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

		if (lines && columns && is_valid_matrix_size)
		{
			incorrectInput = false;
		}
		else
		{
			std::cout << "Wrong dimensions, please try again!\n";
		}
	}
}

void TurnHandler::StartGame()
{
	// variable initialization
	auto playerCharacter = new Character();
	auto enemyCharacter = new Character();
	battlefield = new Battlefield();
	gameEnd = false;
	currentTurn = 0;
	int numberOfPlayers = 0;

	int lines;
	int columns;
	ValidateBattlefieldDimensions(lines, columns);

	battlefield->grid = battlefield->CreateBattleField(lines, columns);
	battlefield->DrawBattlefield(all_players);

	int classIndex = playerCharacter->ValidateClassInput();
	std::string name = playerCharacter->CreateCharacterName();

	playerCharacter = playerCharacter->CreateCharacter(classIndex, name, 1);
	all_players.push_back(playerCharacter);
	numberOfPlayers++;

	classIndex = Shared::GetRandomInt(1, 4);
	name = "Anakin";

	enemyCharacter = enemyCharacter->CreateCharacter(classIndex, name, 2);
	all_players.push_back(enemyCharacter);
	numberOfPlayers++;

	for (Character* player : all_players)
	{
		battlefield->AlocatePlayer(player);
	}

	playerCharacter->SetTarget(enemyCharacter);
	enemyCharacter->SetTarget(playerCharacter);

	int startingPlayer = Shared::GetRandomInt(0, 1);

	while (gameEnd == false)
	{
		StartTurn();


		if (gameEnd == false)
		{
			std::cout << "Current turn: " << ++currentTurn << "\n";
			HandleTurn(startingPlayer);
		}


		if (startingPlayer == 0)
		{
			startingPlayer = 1;
		}
		else
		{
			startingPlayer = 0;
		}
	}
}


void TurnHandler::StartTurn()
{
	if (all_players[0]->health <= 0)
	{
		std::cout << "\nGAME OVER! you lost the game!\n";
		EndGame();
	}
	else if (all_players[1]->health <= 0)
	{
		std::cout << "\nCongratulations! you won the game!\n";
		EndGame();
	}
	else if (gameEnd == false)
	{
		printf("\n");
		printf("Click on any key to start the next turn...\n");
		printf("\n");


		std::cin.get();
	}
}

void TurnHandler::HandleTurn(int starting_player) const
{
	if (starting_player == 0)
	{
		//if we can attack we will attack, else we move 
		const bool can_attack = all_players[0]->CheckCloseTargets(battlefield->grid);
		if (can_attack && all_players[0]->is_dead == false)
		{
			all_players[0]->Attack();
		}
		else
		{
			all_players[0]->MoveToEnemy(battlefield);
			battlefield->DrawBattlefield(all_players);
		}
	}
	else
	{
		const bool can_attack = all_players[1]->CheckCloseTargets(battlefield->grid);
		if (can_attack && all_players[0]->is_dead == false)
		{
			all_players[1]->Attack();
		}
		else
		{
			all_players[1]->MoveToEnemy(battlefield);
			battlefield->DrawBattlefield(all_players);
		}
	}
}

void TurnHandler::EndGame()
{
	std::cout << "the game has ended!";
	gameEnd = true;
	std::cout << "\nPlay again? (y/n): ";
	std::string input;
	getline(std::cin, input);


	if (input == "y" || input=="Y")
	{
		for (const auto player : all_players)
		{
			delete player;
		}

		all_players.clear();

		delete battlefield;

		std::cout.clear();

		system("CLS");

		StartGame();
	}

	else
	{
		gameEnd = true;
		std::cout << "Thank you for playing!";
	}
}
