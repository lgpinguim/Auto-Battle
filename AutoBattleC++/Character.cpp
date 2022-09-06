#include "Grid.h"
#include "Character.h" //deleted the other include, as it was unnecessary.
#include "Types.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "BattleField.h"
#include "Shared.h"

using namespace std;

Character::Character()
= default;

//modernized the destructor class.
Character::~Character()
= default;

//Here we validate if the class input was valid, if not we repeat until the user enter a valid value
int Character::ValidateClassInput() const
{
	//asks for the player to choose between for possible classes via console.
	cout << "Choose Between One of this Classes:\n";
	cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n";

	bool is_choice_needed = true;
	int class_index = 0;

	while (is_choice_needed)
	{
		string choice;
		getline(std::cin, choice);
		class_index = atoi(choice.c_str());

		if (choice.empty() || class_index < 1 || class_index > 4)
		{
			std::cout << "invalid class number input, please try again: \n";
		}
		else
		{
			class_index = atoi(choice.c_str());
			is_choice_needed = false;
		}
	}

	return class_index;
}

//Here we validate if the name input was valid, if not we repeat until the user enter a valid value
string Character::CreateCharacterName() const
{
	string name;
	bool is_choice_needed = true;

	std::cout << "\nCharacter name: ";

	while (is_choice_needed)
	{
		getline(std::cin, name);

		if (name.empty())
		{
			cout << "\nInvalid name input, try again: ";
		}
		else
		{
			is_choice_needed = false;
		}
	}

	return name;
}

//function that will create each character
Character* Character::CreateCharacter(int& classIndex, string& name, int player_index)
{
	const auto character = new Character();

	switch (classIndex)
	{
	case 1:
		{
			//paladins have more health
			character->health = 130;
			character->base_damage = 20;
			character->player_index = player_index;
			character->damage_multiplier = 1.1f;
			character->criticalHitChance = 10;
			character->character_class = Types::CharacterClass::Paladin;
			character->name = name + " the paladin ";
			character->icon = 'P';
			std::cout << "Player " << player_index << " Class Choice: " << "Paladin" << "\n";
			break;
		}
	case 2:
		{
			//warriors more damage
			character->health = 80;
			character->base_damage = 25;
			character->player_index = player_index;
			character->damage_multiplier = 1.1f;
			character->criticalHitChance = 15;
			character->character_class = Types::CharacterClass::Warrior;
			character->name = name + " the warrior";
			character->icon = 'W';
			std::cout << "Player " << player_index << " Class Choice: " << "Warrior" << "\n";
			break;
		}
	case 3:
		{
			//clerics have higher critical damage
			character->health = 100;
			character->base_damage = 15;
			character->player_index = player_index;
			character->damage_multiplier = 3.0f;
			character->criticalHitChance = 15;
			character->character_class = Types::CharacterClass::Cleric;
			character->name = name + " the cleric";
			character->icon = 'C';
			std::cout << "Player " << player_index << " Class Choice: " << "Cleric" << "\n";
			break;
		}
	case 4:
		{
			//archers have higher critical chance
			character->health = 100;
			character->base_damage = 20;
			character->player_index = player_index;
			character->damage_multiplier = 1.5f;
			character->criticalHitChance = 25;
			character->character_class = Types::CharacterClass::Archer;
			character->name = name + " the archer";
			character->icon = 'A';
			std::cout << "Player " << player_index << " Class Choice: " << "Archer" << "\n";
			break;
		}
	default:
		break;
	}

	return character;
}

void Character::TakeDamage(float& amount)
{
	//fixed the amount of damage the player will receive
	if ((health -= amount) <= 0)
	{
		Die();
	}
}

//When the character dies we update the is_dead property.
void Character::Die()
{
	this->is_dead = true;
	std::cout << this->name << " is dead! \n";
}


//In this function we first define who is our character and where he is, after that we get a occupied GridBox index and check if there is any around our character that is occupied.
bool Character::CheckCloseTargets(Grid* battlefield) const
{
	int player_index = this->current_box.index;

	const auto it = find_if(battlefield->grids.begin(), battlefield->grids.end(),
	                             [&player_index](const Types::GridBox& grid_box)
	                             {
		                             return grid_box.occupied == true && grid_box.index != player_index;
	                             });

	//here we check if the acquired location of our enemy is in range of our attacks
	return ((current_box.x_index - 1 == it->x_index && current_box.y_index == it->y_index)
		|| (current_box.x_index + 1 == it->x_index && current_box.y_index == it->y_index)
		|| (current_box.x_index == it->x_index && current_box.y_index + 1 == it->y_index)
		|| (current_box.x_index == it->x_index && current_box.y_index - 1 == it->y_index));
}

//this way we can choose where we should go with more simplicity
void Character::WalkLeft(Battlefield* battlefield, int& list_position)
{
	Move(battlefield, -1, list_position, "left");
}

void Character::WalkRight(Battlefield* battlefield, int& list_position)
{
	Move(battlefield, 1, list_position, "right");
}

void Character::WalkUp(Battlefield* battlefield, int& list_position)
{
	Move(battlefield, -battlefield->grid->y_length, list_position, "up");
}

void Character::WalkDown(Battlefield* battlefield, int& list_position)
{
	Move(battlefield, battlefield->grid->y_length, list_position, "down");
}


//created a main move function that will be used to moeve the character accordingly to the position requested
void Character::Move(Battlefield* battlefield, int offset, int& list_position, string direction)
{
	current_box.occupied = false;
	battlefield->grid->grids[current_box.index] = current_box;
	current_box = (battlefield->grid->grids[current_box.index + (offset)]);
	current_box.occupied = true;
	battlefield->grid->grids[current_box.index] = current_box;
	battlefield->index_location_of_each_player[list_position] = current_box.index;
	std::cout << "Player " << player_index << " walked " << direction << "\n";
}

void Character::MoveToEnemy(Battlefield* battlefield)
{
	//we need to keep the list of player positions updated, so we can print everything on screen accordingly
	int list_position = 0;

	for (int i : battlefield->index_location_of_each_player)
	{
		list_position = i == current_box.index ? 1 : list_position;
	}

	//each one of the ifs below checks where the enemy is and move the character one step closer to it.
	if (current_box.x_index > target->current_box.x_index)
	{
		WalkLeft(battlefield, list_position);
	}
	else if (this->current_box.x_index < target->current_box.x_index)
	{
		WalkRight(battlefield, list_position);
	}
	else if (current_box.y_index > target->current_box.y_index)
	{
		WalkUp(battlefield, list_position);
	}
	else if (current_box.y_index < target->current_box.y_index)
	{
		WalkDown(battlefield, list_position);
	}
}


void Character::Attack() const
{
	//added a crititical chance function so we can use the damage multiplier.

	int critical_chance = Shared::GetRandomInt(0, 100);
	float damage = 0;

	if (critical_chance < criticalHitChance)
	{
		damage = base_damage * damage_multiplier;
	}
	else
	{
		damage = base_damage;
	}

	cout << "Player " << player_index << " is attacking the player " << target->player_index <<
		"  and did " <<
		damage << " damage\n";
	target->TakeDamage(damage);
}
