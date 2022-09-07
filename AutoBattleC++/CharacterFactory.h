#pragma once
#include <string>

class Character;
class Paladin;
class Warrior;
class Cleric;
class Archer;

class CharacterFactory
{
public:

	static Character* CreateCharacter(int& class_index, std::string& name, int player_index);
	
};
