#pragma once
#include "Character.h"

class Paladin : public Character
{
public:

	static Paladin* CreatePaladin(std::string& name, int player_index);

	int block_damage_probability = 25;

	void TakeDamage(float& amount) override;

};
