#pragma once
#include <string>

#include "Character.h"

using namespace std;

class Archer : public Character
{
public:

	static Archer* CreateArcher(std::string& name, int player_index);

	int multiple_attack_probability = 20;

	int max_attacks = 4;

	int min_attacks = 2;

	void Attack() override;

};
