#pragma once
//added string include, se the string class can be used.
#include <string>

#include "Battlefield.h"
#include "Grid.h"
#include "Character.h"
#include "Types.h"

//made a foward declaration to the battlefield class so we can use it here
class Battlefield;

class Character
{
public:
	//Fixed spelling mistakes and created a empty constructor so we can create characters
	Character();
	~Character();


	//standardized the properties names to snake_case, following C++ conventions  and initialized them

	std::string name{};
	float health{};
	float base_damage{};
	float damage_multiplier{};
	//removed comment from GridBox and fixed the name.
	Types::GridBox current_box;
	Types::CharacterClass character_class{};
	int criticalHitChance{}; //added a crititical chance for our characters.
	int player_index{};
	Character* target{};
	bool is_dead{false};
	char icon{'X'};


	// this class should not be anywhere else, we should only create characters using the character class
	static Character* CreateCharacter(int& classIndex, std::string& name, int player_index);

	//created a setter for target
	void SetTarget(Character* t)
	{
		target = t;
	}

	//made this function use the amount variable
	void TakeDamage(float& amount);

	//deleted get index function, it was not implemented or used anywhere 

	//implemented this function.
	void Die();

	//deleted move to function, it was not implemented or used anywhere 
	//refactored this function so now it works better
	bool CheckCloseTargets(Grid* battlefield) const;
	//Created functions so we can choose to where we want to walk with more simplicity.
	void WalkLeft(Battlefield* battlefield, int& list_position);
	void WalkRight(Battlefield* battlefield, int& list_position);
	void WalkUp(Battlefield* battlefield, int& list_position);
	void WalkDown(Battlefield* battlefield, int& list_position);

	//created a move function to simplify our movement, there is no need to have this code repeat when we are moving to any direction
	void Move(Battlefield* battlefield, int offset, int& list_position, std::string direction);

	//a simple validation for the player input
	int ValidateClassInput() const;

	//a simple name validation for the player input
	std::string CreateCharacterName() const;

	//thisFunction is responsible for finding where our character should go, and call the walk function to that direction
	void MoveToEnemy(Battlefield* battlefield);

	//implemented the attack function.
	void Attack() const;
};
