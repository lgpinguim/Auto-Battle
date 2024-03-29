#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <vector>
#include <algorithm>
#include <iostream>

#include "Archer.h"
#include "BattleField.h"
#include "Shared.h"



using namespace std;

Character::Character()
= default;


int Character::ValidateClassInput() const
{
	cout << "Choose Between One of this Classes:\n";
	cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n";

	bool is_choice_needed = true;
	int class_index = 0;

	while (is_choice_needed)
	{
		string choice;
		getline(cin, choice);
		class_index = atoi(choice.c_str());

		if (choice.empty() || class_index < 1 || class_index > 4)
		{
			cout << "invalid class number input, please try again: \n";
		}
		else
		{
			class_index = atoi(choice.c_str());
			is_choice_needed = false;
		}
	}

	return class_index;
}

string Character::CreateCharacterName() const
{
	string inputed_name;
	bool is_choice_needed = true;

	cout << "\nCharacter name: ";

	while (is_choice_needed)
	{
		getline(cin, inputed_name);

		if (inputed_name.empty())
		{
			cout << "\nInvalid name input, try again: ";
		}
		else
		{
			is_choice_needed = false;
		}
	}

	return inputed_name;
}



void Character::TakeDamage(float& amount)
{
	if ((health -= amount) <= 0)
	{
		Die();
	}
}

void Character::Die()
{
	this->is_dead = true;
	cout << this->name << " is dead! \n";
}


bool Character::CheckCloseTargets(Grid* battlefield) const
{
	int player_box_index = this->current_box.index;

	const auto it = find_if(battlefield->grids.begin(), battlefield->grids.end(),
		[&player_box_index](const Types::GridBox& grid_box)
		{
			return grid_box.occupied == true && grid_box.index != player_box_index;
		});

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

void Character::Move(Battlefield* battlefield, int offset, int& list_position, string direction)
{
	current_box.occupied = false;
	battlefield->grid->grids[current_box.index] = current_box;
	current_box = (battlefield->grid->grids[current_box.index + (offset)]);
	current_box.occupied = true;
	battlefield->grid->grids[current_box.index] = current_box;
	battlefield->index_location_of_each_player[list_position] = current_box.index;
	cout << "Player " << player_index << " walked " << direction << "\n";
}

void Character::MoveToEnemy(Battlefield* battlefield)
{
	int list_position = 0;

	for (int iterator : battlefield->index_location_of_each_player)
	{
		list_position = iterator == current_box.index ? 1 : list_position;
	}

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


void Character::Attack()
{
	int critical_chance = Shared::GetRandomInt(0, 100);
	float damage = base_damage;

	if (critical_chance < critical_hit_chance)
	{
		damage *= damage_multiplier;
	}

	cout << "Player " << player_index << " is attacking the player " << target->player_index <<
		"  and did " <<
		damage << " damage\n";
	target->TakeDamage(damage);
}
