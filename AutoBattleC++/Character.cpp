#include "Grid.h"
#include "Character.h" //deleted the other include, as it was unnecessary.
#include "Types.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "BattleField.h"


Character::Character()
= default;

//modernized the destructor class.
Character::~Character()
= default;

int Character::ValidateClassInput() const
{
	//asks for the player to choose between for possible classes via console.
	std::cout << "Choose Between One of this Classes:\n";
	std::cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n";

	bool is_choice_needed = true;
	int class_index = 0;

	while (is_choice_needed)
	{

		std::string choice;
		getline(std::cin, choice);
		class_index = std::atoi(choice.c_str());

		if (choice.empty() || class_index < 1 || class_index > 4)
		{
			std::cout << "invalid class number input, please try again: \n";
		}
		else
		{
			class_index = std::atoi(choice.c_str());
			is_choice_needed = false;
		}
	}

	return class_index;
}

std::string Character::CreateCharacterName() const
{
	std::string name;
	bool is_choice_needed = true;

	std::cout << "\nCharacter name: ";

	while (is_choice_needed)
	{
		getline(std::cin, name);

		if (name.empty())
		{
			std::cout << "\nInvalid name input, try again: ";
			getline(std::cin, name);
		}
		else
		{
			is_choice_needed = false;
		}
	}

	return name;
}

Character* Character::CreateCharacter(int classIndex, std::string name, int player_index)
{
	const auto character = new Character();

	//fixed the switch, so we are comparing numbers, not strings.
	switch (classIndex)
	{
	case 1:
	{
		//paladins have more health
		character->health = 120;
		character->base_damage = 20;
		character->player_index = player_index;
		character->damage_multiplier = 1.1f;
		character->character_class = Types::CharacterClass::Paladin;
		character->name = name + " the paladin ";
		character->icon = 'P';
		std::cout << "Player " << player_index << " Class Choice: " << "Paladin" << "\n";
		break;
	}
	case 2:
	{
		//warriors more damage
		character->health = 100;
		character->base_damage = 25;
		character->player_index = player_index;
		character->damage_multiplier = 1.1f;
		character->character_class = Types::CharacterClass::Warrior;
		character->name = name + " the warrior";
		character->icon = 'W';
		std::cout << "Player " << player_index << " Class Choice: " << "Warrior" << "\n";
		break;
	}
	case 3:
	{
		//clerics have hihger critical damage
		character->health = 100;
		character->base_damage = 15;
		character->player_index = player_index;
		character->damage_multiplier = 2.0f;
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

void Character::TakeDamage(float amount)
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
bool Character::CheckCloseTargets(Grid * battlefield) const
{
	int player_index = this->current_box.index;

	const auto it = std::find_if(battlefield->grids.begin(), battlefield->grids.end(),
		[&player_index](const Types::GridBox& grid_box)
		{
			return grid_box.occupied == true && grid_box.index !=
				player_index;
		});

	//here we check if the acquired location of our enemy is in range of our attacks
	return ((current_box.x_index - 1 == it->x_index && current_box.y_index == it->y_index)
		|| (current_box.x_index + 1 == it->x_index && current_box.y_index == it->y_index)
		|| (current_box.x_index == it->x_index && current_box.y_index + 1 == it->y_index)
		|| (current_box.x_index == it->x_index && current_box.y_index - 1 == it->y_index));
}

void Character::WalkLeft(Battlefield * battlefield, int listPosition)
{
	Move(battlefield, -1, listPosition, "left");
}

void Character::WalkRight(Battlefield * battlefield, int listPosition)
{
	Move(battlefield, 1, listPosition, "right");
}

void Character::WalkUp(Battlefield * battlefield, int listPosition)
{
	Move(battlefield, -battlefield->grid->y_length, listPosition, "up");
}

void Character::WalkDown(Battlefield * battlefield, int listPosition)
{
	Move(battlefield, battlefield->grid->y_length, listPosition, "down");
}

void Character::Move(Battlefield * battlefield, int offset, int listPosition, std::string direction)
{
	current_box.occupied = false;
	battlefield->grid->grids[current_box.index] = current_box;
	current_box = (battlefield->grid->grids[current_box.index + (offset)]);
	current_box.occupied = true;
	battlefield->grid->grids[current_box.index] = current_box;
	battlefield->index_location_of_each_player[listPosition] = current_box.index;
	std::cout << "Player " << player_index << " walked " << direction << "\n";
}

void Character::MoveToEnemy(Battlefield * battlefield)
{
	//we need to keep the list of player positions updated, so we can print everything on screen accordingly
	int listPosition = 0;

	for (int i : battlefield->index_location_of_each_player)
	{

		listPosition = i == current_box.index ? 1 : listPosition;

	}

	//each one of the ifs below checks where the enemy is and move the character one step closer to it.
	if (current_box.x_index > target->current_box.x_index)
	{
		WalkLeft(battlefield, listPosition);
	}
	else if (this->current_box.x_index < target->current_box.x_index)
	{
		WalkRight(battlefield, listPosition);
	}
	else if (current_box.y_index > target->current_box.y_index)
	{
		WalkUp(battlefield, listPosition);
	}
	else if (current_box.y_index < target->current_box.y_index)
	{
		WalkDown(battlefield, listPosition);
	}
}


void Character::Attack() const
{
	std::cout << "Player " << this->player_index << " is attacking the player " << this->target->player_index <<
		"  and did " <<
		this->base_damage << " damage\n";
	target->TakeDamage(this->base_damage);
}
