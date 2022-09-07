#include "Warrior.h"

#include <iostream>

#include "Shared.h"

using namespace std;

Warrior* Warrior::CreateWarrior(std::string& name, int player_index)
{
	const auto character = new Warrior();
	character->health = 80;
	character->base_damage = 25;
	character->player_index = player_index;
	character->damage_multiplier = 1.1f;
	character->critical_hit_chance = 15;
	character->character_class = CharacterClass::Warrior;
	character->name = name + " the warrior";
	character->icon = 'W';
	cout << "Player " << player_index << " Class Choice: " << "Warrior" << "\n";
	return character;
}

void Warrior::Attack()
{
	int double_damage_chance = Shared::GetRandomInt(0, 100);
	float damage = base_damage;

	if (double_damage_chance <= double_damage_probability)
	{
		damage *= 2;

		std::cout << "Player " << player_index << " has done double damage! the player " << target->player_index <<
			"  takes " << damage << " damage\n";
		target->TakeDamage(damage);
		return;
	}

	ICharacter::Attack();

}
