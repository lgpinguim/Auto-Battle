#include "Grid.h"
#include "Character.h" //deleted the other include, as it was unnecessary.
#include "Types.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
Character::Character()
= default;

//modernized the destructor class.
Character::~Character()
= default;

Character* Character::CreateCharacter(int classIndex)
{
	const auto character = new Character();

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
		character->name = "Brown the paladin\n";
		character->icon = 'P';
		std::cout << "Player Class Choice: " << character->character_class << "\n";
		break;
	}
	case 2:
	{
		//warriors more damage
		character->Health = 100;
		character->BaseDamage = 25;
		character->PlayerIndex = 0;
		character->DamageMultiplier = 1.1f;
		character->CritChance = 0.10f;
		character->characterClass = Types::Warrior;
		character->Name = "Mingau the warrior";
		std::cout << "Player Class Choice: " << character->characterClass << "\n";
		break;
	}
	case 3:
	{
		//clerics have higer critical damage
		character->Health = 100;
		character->BaseDamage = 15;
		character->PlayerIndex = 0;
		character->DamageMultiplier = 2.0f;
		character->CritChance = 0.10f;
		character->characterClass = Types::Cleric;
		character->Name = "Joseph the cleric";
		std::cout << "Player Class Choice: " << character->characterClass << "\n";
		break;
	}
	case 4:
	{
		//archers have higher critical chance
		character->Health = 100;
		character->BaseDamage = 20;
		character->PlayerIndex = 0;
		character->DamageMultiplier = 1.5f;
		character->CritChance = 0.30f;
		character->characterClass = Types::Archer;
		character->Name = "Meliante the archer";
		std::cout << "Player Class Choice: " << character->characterClass << "\n";
		break;
	}
	default:
		std::cout << "invalid input, please try again: \n";
		std::string choice;

		getline(std::cin, choice);

		const int numericChoice = std::stoi(choice);

		create_player_character(numericChoice);
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

void Character::Die() 
{
    //When the character dies we update the is_dead property.
    this->is_dead = true;
    std::cout << this->name << " is dead!";
}

void Character::WalkTo(bool CanWalk) 
{

}



void Character::StartTurn(Grid* battlefield) {

    {

        if (CheckCloseTargets(battlefield))
        {
            Attack(Character::target);


            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
            
            
            if (current_box.x_index > target->current_box.x_index)
            {
                if(find(battlefield->grids.begin(), battlefield->grids.end(), current_box.index - 1) != battlefield->grids.end())
                
                {
                    current_box.occupied = false;
                    battlefield->grids[current_box.index] = current_box;
                    current_box = (battlefield->grids[current_box.index - 1]);
                    current_box.occupied = true;
                    battlefield->grids[current_box.index] = current_box;
                    //Console.WriteLine($"Player {PlayerIndex} walked left\n");
                    battlefield->drawBattlefield(5, 5);

                    return;
                }
            }
            else if (current_box.x_index < target->current_box.x_index)
            {
                current_box.occupied = false;
                battlefield->grids[current_box.index] = current_box;
                current_box = (battlefield->grids[current_box.index + 1]);
                return;
                battlefield->grids[current_box.index] = current_box;
                //Console.WriteLine($"Player {PlayerIndex} walked right\n");
                battlefield->drawBattlefield(5, 5);
            }

            if (current_box.y_index > target->current_box.y_index)
            {
                battlefield->drawBattlefield(5, 5);
                current_box.occupied = false;
                battlefield->grids[current_box.index] = current_box;
                current_box = battlefield->grids[(current_box.index - battlefield->x_length)];
                current_box.occupied = true;
                battlefield->grids[current_box.index] = current_box;
                //Console.WriteLine($"PlayerB {PlayerIndex} walked up\n");
                return;
            }
            else if (current_box.y_index < target->current_box.y_index)
            {
                current_box.occupied = true;
                battlefield->grids[current_box.index] = current_box;
                current_box = battlefield->grids[current_box.index + battlefield->x_length];
                current_box.occupied = false;
                battlefield->grids[current_box.index] = current_box;
                //Console.WriteLine($"Player {PlayerIndex} walked down\n");
                battlefield->drawBattlefield(5, 5);

                return;
            }
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{

}

void Character::MoveToEnemy()
{
}

void Character::Attack(Character* target) 
{

}

