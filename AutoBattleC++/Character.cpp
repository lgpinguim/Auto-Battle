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

Character* Character::CreateCharacter(int classIndex)
{
	//added the ability to name our characters.
	const auto character = new Character();

	std::string	charName;

	std::cout << "\nCharacter name: ";

	getline(std::cin, charName);

	switch (classIndex)
	{
	case 1:
	{
		//paladins have more health
		character->health = 120;
		character->base_damage = 20;
		character->player_index = 0;
		character->damage_multiplier = 1.1f;
		character->character_class = Types::Paladin;
		character->name = charName + " the paladin\n";
		character->icon = 'P';
		std::cout << "Player Class Choice: " << character->character_class << "\n";
		break;
	}
	case 2:
	{
		//warriors more damage
		character->health = 100;
		character->base_damage = 25;
		character->player_index = 0;
		character->damage_multiplier = 1.1f;
		character->character_class = Types::Warrior;
		character->name = charName + " the warrior";
		std::cout << "Player Class Choice: " << character->character_class << "\n";
		break;
	}
	case 3:
	{
		//clerics have higer critical damage
		character->health = 100;
		character->base_damage = 15;
		character->player_index = 0;
		character->damage_multiplier = 2.0f;
		character->character_class = Types::Cleric;
		character->name = charName + " the cleric";
		std::cout << "Player Class Choice: " << character->character_class << "\n";
		break;
	}
	case 4:
	{
		//archers have higher critical chance
		character->health = 100;
		character->base_damage = 20;
		character->player_index = 0;
		character->damage_multiplier = 1.5f;
		character->character_class = Types::Archer;
		character->name = charName + " the archer";
		std::cout << "Player Class Choice: " << character->character_class << "\n";
		break;
	}
	default:
		std::cout << "invalid input, please try again: \n";
		std::string choice;

		getline(std::cin, choice);

		const int numericChoice = std::stoi(choice);

		CreateCharacter(numericChoice);
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
	std::cout << this->name << " is dead!";
}


//In this function we first define who is our character and where he is, after that we get a occupied GridBox index and check if there is any around our character that is occupied.
bool Character::CheckCloseTargets(Grid * battlefield) const
{

	int Playerindex = this->current_box.index;

	const auto it = std::find_if(battlefield->grids.begin(), battlefield->grids.end(),
		[&Playerindex](const Types::GridBox& grid_box)
		{
			return grid_box.occupied == true && grid_box.index !=
				Playerindex;
		});

	//here we check if the acquired location of our enemy is in range of our attacks
	if (this->current_box.x_index - 1 == it->x_index && this->current_box.y_index == it->y_index)
	{
		return true;
	}
	else if (this->current_box.x_index + 1 == it->x_index && this->current_box.y_index == it->y_index)
	{
		return true;
	}
	else if (this->current_box.x_index == it->x_index && this->current_box.y_index + 1 == it->y_index)
	{
		return true;
	}
	else if (this->current_box.x_index == it->x_index && this->current_box.y_index - 1 == it->y_index)
	{
		return true;
	}

	return false;
}

void Character::MoveToEnemy(Battlefield* battlefield)
{
	//we need to keep the list of player positions updated, so we can print everything on screen accordingly
	int listPosition=0;

	for(int i = 0; i< battlefield->index_location_of_each_player.size();i++)
	{
		if (battlefield->index_location_of_each_player[i] == current_box.index)
		{
			listPosition = i;
		}
	}

	//each one of the ifs below checks where the enemy is and move the character one step closer to it.

	if (current_box.x_index > target->current_box.x_index)
	{
		current_box.occupied = false;
		battlefield->grid->grids[current_box.index] = current_box;
		current_box = (battlefield->grid->grids[current_box.index - 1]);
		current_box.occupied = true;
		battlefield->grid->grids[current_box.index] = current_box;
		battlefield->index_location_of_each_player[listPosition] = current_box.index;
		std::cout << "Player " << player_index << " walked left\n";
	}
	else if (this->current_box.x_index < target->current_box.x_index)
	{
		current_box.occupied = false;
		battlefield->grid->grids[current_box.index] = current_box;
		current_box = (battlefield->grid->grids[current_box.index + 1]);
		current_box.occupied = true;
		battlefield->grid->grids[current_box.index] = current_box;
		battlefield->index_location_of_each_player[listPosition] = current_box.index;
		std::cout << "Player " << player_index << " walked right\n";
	}
	else if (current_box.y_index > target->current_box.y_index)
	{
		current_box.occupied = false;
		battlefield->grid->grids[current_box.index] = current_box;
		current_box = (battlefield->grid->grids[current_box.index - battlefield->grid->y_length]);
		current_box.occupied = true;
		battlefield->grid->grids[current_box.index] = current_box;
		battlefield->index_location_of_each_player[listPosition] = current_box.index;
		std::cout << "Player " << player_index << " walked up\n";
	}
	else if (current_box.y_index < target->current_box.y_index)
	{
		current_box.occupied = false;
		battlefield->grid->grids[current_box.index] = current_box;
		current_box = (battlefield->grid->grids[current_box.index + battlefield->grid->y_length]);
		current_box.occupied = true;
		battlefield->grid->grids[current_box.index] = current_box;
		battlefield->index_location_of_each_player[listPosition] = current_box.index;
		std::cout << "Player " << player_index << " walked down\n";
	}

}


void Character::Attack() const
{
	target->TakeDamage(this->base_damage);
	std::cout << "Player " << this->player_index << " is attacking the player " << this->target->player_index << "  and did " <<
		this->base_damage << " damage\n";
}

