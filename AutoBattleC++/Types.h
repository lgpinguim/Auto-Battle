#pragma once
class Types
{
public:
	//standardized the code for properties, variable names and functions.
	struct GridBox
	{
		int x_index{};
		int y_index{};
		bool occupied{false};
		int index{};

		//constructor with the variables initialized
		GridBox(const int x, const int y, const int index) : x_index(x), y_index(y), index(index)
		{
		}

		GridBox() = default;
	};

	// we should use enum classes instead of enum, this was generating a compilation warning
	enum class CharacterClass
	{
		Paladin = 1,
		Warrior = 2,
		Cleric = 3,
		Archer = 4
	};
};
