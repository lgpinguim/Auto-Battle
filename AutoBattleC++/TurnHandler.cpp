#include "TurnHandler.h"

#include <iostream>

#include "Battlefield.h"
#include "Shared.h"


TurnHandler::TurnHandler()
= default;

//modernized the destructor class.
TurnHandler::~TurnHandler()
= default;



void TurnHandler::StartGame()
{
	// variable initialization
	auto player_character = new Character();
	auto enemy_character = new Character();
	battlefield = new Battlefield();
	game_end = false;
	current_turn = 0;
	int lines;
	int columns;

	//here we validate the input creation of the battlefield
	battlefield->ValidateBattlefieldDimensions(lines, columns);
	battlefield->grid = battlefield->CreateBattleField(lines, columns);
	battlefield->DrawBattlefield(all_players);

	//input for class and name validation
	int class_index = player_character->ValidateClassInput();
	std::string name = player_character->CreateCharacterName();

	//player character validation
	player_character = Character::CreateCharacter(class_index, name, 1);
	all_players.push_back(player_character);

	//enemy creation
	class_index = Shared::GetRandomInt(1, 4);
	name = "Anakin";
	enemy_character = Character::CreateCharacter(class_index, name, 2);
	all_players.push_back(enemy_character);

	//target setting
	player_character->SetTarget(enemy_character);
	enemy_character->SetTarget(player_character);

	//alocation of all characters to the battlefield
	for (Character* player : all_players)
	{
		battlefield->AlocatePlayer(player);
	}

	//a simple random to determine who will start the game
	int startingPlayer = Shared::GetRandomInt(0, 1);

	//here is where our turns will happen
	while (game_end == false)
	{
		StartTurn();

		if (game_end == false)
		{
			std::cout << "Current turn: " << ++current_turn << "\n";
			HandleTurn(startingPlayer);
		}

		startingPlayer = startingPlayer == 0 ? 1 : 0;

	}
}

//on the beginning of each turn we check if anyone died and end the game if that is true, if not we continue the turn.
void TurnHandler::StartTurn()
{
	if (all_players[0]->health <= 0)
	{
		std::cout << "\nGAME OVER! you lost the game!\n";
		EndGame();
	}
	else if (all_players[1]->health <= 0)
	{
		std::cout << "\nCongratulations! "  << all_players[0]->name <<  "won the game!\n";
		EndGame();
	}
	else if (game_end == false)
	{
		printf("\n");
		printf("Click on any key to start the next turn...\n");
		printf("\n");
		std::cin.get();
	}
}

//here each character will have the opportunity to check if the enemy is close and move, or attack.
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

//Here we finish the game and ask if the player wants another round
void TurnHandler::EndGame()
{
	std::cout << "the game has ended!";
	game_end = true;
	std::cout << "\nPlay again? (y/n): ";
	std::string input;
	getline(std::cin, input);


	if (input == "y" || input=="Y")
	{
		//here we dealocate and delete our pointers so we wont use more memory each time we run
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
		game_end = true;
		std::cout << "Thank you for playing!";
	}
}
