#include <string>
#pragma once

class Constants
{
public:
	static void ReadFile();
	static float GetConstant(std::string constName);

private:
	static const int NUM_CONST = 50;

	struct Constant
	{
		std::string name;
		float value;
	};

	static Constant ConstantsList[NUM_CONST];
};
