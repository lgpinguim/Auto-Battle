#include "CharacterFactory.h"

#include "Archer.h"
#include "Cleric.h"
#include "Paladin.h"
#include "Warrior.h"

Character* CharacterFactory::CreateCharacter(int& class_index, std::string& name, int player_index)
{
	auto character = new Character();

	switch (class_index)
	{
	case 1:
	{
		//Paladins have a chance of blocking damage
		character = Paladin::CreatePaladin(name, player_index);
		break;
	}
	case 2:
	{
		//warriors have a chance of dealing double damage
		character = Warrior::CreateWarrior(name, player_index);
		break;
	}
	case 3:
	{
		//clerics can recover health
		character = Cleric::CreateCleric(name, player_index);
		break;
	}
	case 4:
	{
		//archers have higher critical chance
		character = Archer::CreateArcher(name, player_index);
		break;
	}
	default:
		break;
	}

	return character;
}
