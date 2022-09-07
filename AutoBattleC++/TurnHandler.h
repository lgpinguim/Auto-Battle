#pragma once
#include <Vector>

class Battlefield;
class Character;

class TurnHandler
{
public:
	//Created this class to better segregate the responsibilities between classes
	//This class will be responsible for handling the turns of the game.
	TurnHandler();
	void SetupBattlefield();
	void SetupPlayers();
	void AllocatePlayersOnBattlefield() const;

	//List of players
	std::vector<Character*> all_players;

	//Battlefield
	Battlefield* battlefield{};
	//variable used to set the flow of the game
	bool game_end{false};
	//counter of how many turns we have
	int current_turn{};


	//builds everything needed by the game
	void StartGame();

	void SetUpGame();
	void FlipPlayerTurn(int& starting_player);

	//starts the turn and sets who will play
	void StartTurn();

	// function responsible for handling the current turn
	void HandleTurn(Character* player) const;

	//finishes the game
	void EndGame();
};
