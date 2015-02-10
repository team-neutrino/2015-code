#include <string>
#pragma once

class Constants
{
public:
	Constants();

	/**
	 * Reads in constants from file and overrides defaults.
	 */
	static void ReadFile();

	/**
	 * Returns the value of the constant with the given name.
	 */
	static float GetConstant(std::string constName);

private:
	static const int NUM_CONST = 50;

	struct Constant
	{
		std::string name;
		float value;
	};

	static Constant ConstantsList[NUM_CONST];

	static void overrideConst(std::string line);
};
