#pragma once
#include <string>

class ICharacter;
class Paladin;
class Warrior;
class Cleric;
class Archer;

class CharacterFactory
{
public:

	static ICharacter* CreateCharacter(int& class_index, std::string& name, int player_index);
	
};
