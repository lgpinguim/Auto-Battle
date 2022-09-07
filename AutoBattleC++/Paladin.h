#pragma once
#include "ICharacter.h"

class Paladin : public ICharacter
{
public:

	static Paladin* CreatePaladin(std::string& name, int player_index);

	int block_damage_probability = 25;

	void TakeDamage(float& amount) override;

};
