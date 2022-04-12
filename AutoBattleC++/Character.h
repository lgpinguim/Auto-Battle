#pragma once
//added string include, se the string class can be used.
#include <string>

#include "Battlefield.h"
#include "Grid.h"
#include "Character.h"
#include "Types.h"


class Character
{
public:

	//Fixed spelling mistakes and created a empty constructor so we can create characters
	Character();
	~Character();

	//standardized the properties names to snake_case, following C++ conventions 

	std::string name;
	float health{};
	float base_damage{};
	float damage_multiplier{};
	//removed comment from GridBox and fixed the name.
	Types::GridBox current_box;
	Types::CharacterClass character_class;
	int player_index{};
	Character* target{};
	bool is_dead{false};
	char icon{'X'};

	
	// this class should not be anywhere else, we should only create characters using the character class
	Character* CreateCharacter(int classIndex);

	void TakeDamage(float amount);

	//deleted get index function, it was not implemented or used anywhere 

	void Die();

	//deleted move to function, it was not implemented or used anywhere 

	bool CheckCloseTargets(Grid* battlefield) const;

	void MoveToEnemy(Battlefield* battlefield);

	void Attack() const;


};


