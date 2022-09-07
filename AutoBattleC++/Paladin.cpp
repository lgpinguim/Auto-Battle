#include "Paladin.h"

#include <iostream>

#include "Shared.h"

using namespace std;

Paladin* Paladin::CreatePaladin(string& name, int player_index)
{
	const auto character = new Paladin();
	character->health = 130;
	character->base_damage = 20;
	character->player_index = player_index;
	character->damage_multiplier = 1.1f;
	character->critical_hit_chance = 10;
	character->character_class = CharacterClass::Paladin;
	character->name = name + " the paladin ";
	character->icon = 'P';
	cout << "Player " << player_index << " Class Choice: " << "Paladin" << "\n";

	return character;
}

void Paladin::TakeDamage(float& amount)
{
	int block_damage_chance = Shared::GetRandomInt(0, 100);

	if (block_damage_chance <= block_damage_probability)
	{
		std::cout << "Player " << player_index << " has blocked the damage! player " << target->player_index <<
			"  did  0" << " damage\n";
	}
	else
	{
		if ((health -= amount) <= 0)
		{
			Die();
		}
	}

}
