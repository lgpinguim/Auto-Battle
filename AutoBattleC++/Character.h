#pragma once
#include <string>

#include "Battlefield.h"
#include "Grid.h"
#include "Character.h"
#include "Types.h"

enum class CharacterClass;
class Battlefield;

class Character
{
public:
	Character();

	std::string name{};
	float health{};
	float base_damage{};
	float damage_multiplier{};
	Types::GridBox current_box;
	CharacterClass character_class{};
	int critical_hit_chance{}; 
	int player_index{};
	Character* target{};
	bool is_dead{false};
	char icon{'X'};

	static Character* CreateCharacter(int& class_index, std::string& name, int player_index);

	void SetTarget(Character* t)
	{
		target = t;
	}

	void TakeDamage(float& amount);

	void Die();

	bool CheckCloseTargets(Grid* battlefield) const;

	void WalkLeft(Battlefield* battlefield, int& list_position);
	void WalkRight(Battlefield* battlefield, int& list_position);
	void WalkUp(Battlefield* battlefield, int& list_position);
	void WalkDown(Battlefield* battlefield, int& list_position);

	void Move(Battlefield* battlefield, int offset, int& list_position, std::string direction);

	int ValidateClassInput() const;

	std::string CreateCharacterName() const;

	void MoveToEnemy(Battlefield* battlefield);

	void Attack() const;
};

enum class CharacterClass
{
	Paladin = 1,
	Warrior = 2,
	Cleric = 3,
	Archer = 4
};
