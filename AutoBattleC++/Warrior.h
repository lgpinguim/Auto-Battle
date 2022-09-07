#pragma once
#include <string>

#include "Character.h"

class Warrior : public Character
{
public:

	static Warrior* CreateWarrior(std::string& name, int player_index);

	int double_damage_probability = 25;

	void Attack() override;

};

