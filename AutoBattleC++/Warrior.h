#pragma once
#include <string>

#include "ICharacter.h"

class Warrior : public ICharacter
{
public:

	static Warrior* CreateWarrior(std::string& name, int player_index);

	int double_damage_probability = 25;

	void Attack() override;

};
