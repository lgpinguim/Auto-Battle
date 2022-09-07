#include "Archer.h"

#include <iostream>

#include "Shared.h"

using namespace std;

Archer* Archer::CreateArcher(std::string& name, int player_index)
{
	auto character = new Archer();
	character->health = 100;
	character->base_damage = 20;
	character->player_index = player_index;
	character->damage_multiplier = 1.5f;
	character->critical_hit_chance = 25;
	character->character_class = CharacterClass::Archer;
	character->name = name + " the archer";
	character->icon = 'A';
	cout << "Player " << player_index << " Class Choice: " << "Archer" << "\n";
	return character;
}

void Archer::Attack()
{
	int multiple_attack_chance = Shared::GetRandomInt(0, 100);

	if (multiple_attack_chance <= multiple_attack_probability)
	{
		std::cout << "Player " << player_index << " has used multiple attacks!\n";
		int hits = Shared::GetRandomInt(min_attacks, max_attacks);
		for (int i = 0; i < hits; i++) {
			Character::Attack();
		}
		return;
	}

	Character::Attack();
}
