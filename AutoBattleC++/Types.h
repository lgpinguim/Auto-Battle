#pragma once
class Types
{
public:
	//standardized the code for properties, variable names and functions.
	struct GridBox
	{
		int x_index{};
		int y_index{};
		bool occupied{};
		int index{};

		GridBox(int x, int y, bool occupied, int index) : x_index(x), y_index(y), occupied(false), index(index)
		{
		}

		GridBox() = default;
	};

	enum class CharacterClass
	{
		Paladin = 1,
		Warrior = 2,
		Cleric = 3,
		Archer = 4
	};
};
