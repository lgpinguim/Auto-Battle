#pragma once
#include <Vector>

class Battlefield;
class Character;
class CharacterFactory;

class TurnHandler
{
public:

	TurnHandler();
	void SetupBattlefield();
	void SetupPlayers();
	void AllocatePlayersOnBattlefield() const;

	std::vector<Character*> all_players;

	//Battlefield
	Battlefield* battlefield{};
	bool game_end{false};
	int current_turn{};

	void StartGame();

	void SetUpGame();

	static void FlipPlayerTurn(int& starting_player);

	void StartTurn();

	void HandleTurn(Character* player) const;

	void EndGame();
};
