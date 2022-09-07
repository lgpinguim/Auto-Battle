#pragma once
class Types
{
public:
	struct GridBox
	{
		int x_index{};
		int y_index{};
		bool occupied{false};
		int index{};

		GridBox(const int x, const int y, const int index) : x_index(x), y_index(y), index(index)
		{
		}

		GridBox() = default;
	};

};
