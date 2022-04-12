#pragma once
#include <Vector>

class Battlefield;
class Character;

class TurnHandler
{
public:
	//Created this class to beter segregate the responsibilities between classes
	//This class will be responsible for handling the turns of the game.


	//List of players
	std::vector<Character*> all_players;

	//Battlefield
	Battlefield* battlefield{};

	bool gameEnd{false};

	int currentTurn{};


	TurnHandler();
	~TurnHandler();
	void ValidateBattlefieldDimensions(int& lines, int& columns);
	//builds everything needed by the game
	void StartGame();

	//starts the turn and sets who will play
	void StartTurn();

	// function responsible for handling the current turn
	void HandleTurn(int starting_player);

	//finishes the game
	void EndGame();
};
