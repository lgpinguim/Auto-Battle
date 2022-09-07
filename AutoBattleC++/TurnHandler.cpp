#include "TurnHandler.h"

#include <iostream>

#include "Battlefield.h"
#include "CharacterFactory.h"
#include "Shared.h"


using namespace std;

TurnHandler::TurnHandler()
= default;


void TurnHandler::SetupBattlefield()
{
	int lines;
	int columns;

	battlefield = new Battlefield();
	battlefield->ValidateBattlefieldDimensions(lines, columns);
	battlefield->grid = battlefield->CreateBattleField(lines, columns);
}

void TurnHandler::SetupPlayers()
{
	auto player_character = new ICharacter();
	int class_index = player_character->ValidateClassInput();
	string name = player_character->CreateCharacterName();
	player_character = CharacterFactory::CreateCharacter(class_index, name, 1);
	all_players.push_back(player_character);

	//enemy creation
	class_index = Shared::GetRandomInt(1, 4);
	name = "Anakin";
	const auto enemy_character = CharacterFactory::CreateCharacter(class_index, name, 2);
	all_players.push_back(enemy_character);

	player_character->SetTarget(enemy_character);
	enemy_character->SetTarget(player_character);
}

void TurnHandler::AllocatePlayersOnBattlefield() const
{
	for (ICharacter* player : all_players)
	{
		battlefield->AlocatePlayer(player);
	}
}

void TurnHandler::SetUpGame()
{
	// variable initialization
	game_end = false;
	current_turn = 0;

	SetupPlayers();

	SetupBattlefield();

	AllocatePlayersOnBattlefield();

	battlefield->DrawBattlefield(all_players);

}

void TurnHandler::FlipPlayerTurn(int& starting_player)
{
	starting_player = starting_player == 0 ? 1 : 0;
}

void TurnHandler::StartGame()
{
	SetUpGame();

	int starting_player = Shared::GetRandomInt(0, 1);

	while (!game_end)
	{
		StartTurn();

		if (!game_end)
		{
			cout << "Current turn: " << ++current_turn << "\n";
			HandleTurn(all_players[starting_player]);
		}

		FlipPlayerTurn(starting_player);
	}
}

void TurnHandler::StartTurn()
{
	if (all_players[0]->health <= 0)
	{
		cout << "\nGAME OVER! you lost the game!\n";
		EndGame();
	}
	else if (all_players[1]->health <= 0)
	{
		cout << "\nCongratulations! " << all_players[0]->name << " won the game!\n";
		EndGame();
	}
	else if (!game_end)
	{
		printf("\n");
		system("pause");
		printf("\n");
	}
}

void TurnHandler::HandleTurn(ICharacter* player) const
{
	bool can_attack = player->CheckCloseTargets(battlefield->grid);
	if (can_attack)
	{
		player->Attack();
	}

	else
	{
		player->MoveToEnemy(battlefield);
		battlefield->DrawBattlefield(all_players);
		can_attack = player->CheckCloseTargets(battlefield->grid);
		if (can_attack)player->Attack();
	}
}

void TurnHandler::EndGame()
{
	cout << "the game has ended!";
	game_end = true;
	cout << "\nPlay again? (y/n): ";
	string input;
	getline(cin, input);

	if (input == "y" || input == "Y")
	{
		for (const auto player : all_players)
		{
			delete player;
		}

		all_players.clear();

		delete battlefield;

		system("cls");

		StartGame();
	}

	else
	{
		game_end = true;
		cout << "Thank you for playing!";
	}
}
