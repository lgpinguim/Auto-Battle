#pragma once
#include <string>

#include "Battlefield.h"
#include "Grid.h"
#include "ICharacter.h"
#include "Types.h"

enum class CharacterClass;
class Battlefield;
class Paladin;
class Warrior;
class Cleric;
class Archer;

class ICharacter
{
public:
	virtual ~ICharacter() = default;
	ICharacter();

	std::string name{};
	float health{};
	float base_damage{};
	float damage_multiplier{};
	Types::GridBox current_box;
	CharacterClass character_class{};
	int critical_hit_chance{};
	int player_index{};
	ICharacter* target{};
	bool is_dead{ false };
	char icon{ 'X' };

	

	int ValidateClassInput() const;

	std::string CreateCharacterName() const;

	void SetTarget(ICharacter* t)
	{
		target = t;
	}

	virtual bool CheckCloseTargets(Grid* battlefield) const;

	virtual void MoveToEnemy(Battlefield* battlefield);

	virtual void Attack();

	virtual void TakeDamage(float& amount);

	void Die();


private:

	void Move(Battlefield* battlefield, int offset, int& list_position, std::string direction);
	void WalkLeft(Battlefield* battlefield, int& list_position);
	void WalkRight(Battlefield* battlefield, int& list_position);
	void WalkUp(Battlefield* battlefield, int& list_position);
	void WalkDown(Battlefield* battlefield, int& list_position);
};



enum class CharacterClass
{
	Paladin = 1,
	Warrior = 2,
	Cleric = 3,
	Archer = 4
};
