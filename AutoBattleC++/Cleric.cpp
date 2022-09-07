#include "Cleric.h"

#include <iostream>

#include "Shared.h"

using namespace std;

Cleric* Cleric::CreateCleric(std::string& name, int player_index)
{
	const auto character = new Cleric();
	character->health = 100;
	character->base_damage = 15;
	character->player_index = player_index;
	character->damage_multiplier = 3.0f;
	character->critical_hit_chance = 15;
	character->character_class = CharacterClass::Cleric;
	character->name = name + " the cleric";
	character->icon = 'C';
	cout << "Player " << player_index << " Class Choice: " << "Cleric" << "\n";
	return character;
}

void Cleric::Attack()
{
	int health_regen_chance = Shared::GetRandomInt(0, 100);


	if (health_regen_chance <= health_regen_probability)
	{
		health += heal_amount;

		std::cout << "Player " << player_index << " has healed for " << heal_amount << " hp!\n";
	}

	Character::Attack();
}
