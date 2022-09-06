#include "TurnHandler.h"

#include <iostream>

#include "Battlefield.h"
#include "Shared.h"


using namespace std;

TurnHandler::TurnHandler()
= default;


void TurnHandler::SetUpGame()
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
	string name = player_character->CreateCharacterName();

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
}

void TurnHandler::FlipPlayerTurn(int& starting_player)
{
	starting_player = starting_player == 0 ? 1 : 0;
}

void TurnHandler::StartGame()
{
	SetUpGame();

	//a simple random to determine who will start the game
	int starting_player = Shared::GetRandomInt(0, 1);

	//here is where our turns will happen
	while (game_end == false)
	{
		StartTurn();

		if (game_end == false)
		{
			cout << "Current turn: " << ++current_turn << "\n";
			HandleTurn(all_players[starting_player]);
		}

		FlipPlayerTurn(starting_player);
	}
}

//on the beginning of each turn we check if anyone died and end the game if that is true, if not we continue the turn.
void TurnHandler::StartTurn()
{
	if (all_players[0]->health <= 0)
	{
		cout << "\nGAME OVER! you lost the game!\n";
		EndGame();
	}
	else if (all_players[1]->health <= 0)
	{
		cout << "\nCongratulations! " << all_players[0]->name << "won the game!\n";
		EndGame();
	}
	else if (game_end == false)
	{
		printf("\n");
		system("pause");
		printf("\n");
	}
}

void TurnHandler::HandleTurn(Character* player) const
{
	const bool can_attack = player->CheckCloseTargets(battlefield->grid);
	if (can_attack)
	{
		player->Attack();
		return;
	}

	player->MoveToEnemy(battlefield);
	battlefield->DrawBattlefield(all_players);
}

//Here we finish the game and ask if the player wants another round
void TurnHandler::EndGame()
{
	cout << "the game has ended!";
	game_end = true;
	cout << "\nPlay again? (y/n): ";
	string input;
	getline(cin, input);

	if (input == "y" || input == "Y")
	{
		//here we dealocate and delete our pointers so we wont use more memory each time we run
		for (const auto player : all_players)
		{
			delete player;
		}

		all_players.clear();

		delete battlefield;

		cout.clear();

		StartGame();
	}

	else
	{
		game_end = true;
		cout << "Thank you for playing!";
	}
}
