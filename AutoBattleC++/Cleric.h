#pragma once
#include <string>

#include "Character.h"

class Cleric : public Character
{
public:

	static Cleric* CreateCleric(std::string& name, int player_index);

	int health_regen_probability = 25;
	float heal_amount = 5;

	void Attack() override;

};
