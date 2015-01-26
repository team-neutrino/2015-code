#include "Constants.h"
#include "WPILib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

Constants::Constant Constants::ConstantsList[NUM_CONST] =
{
		// Main Constants
		{"constant1", 23},
		{"constant2", 48},
		{"constant3", 25},
		{"constant4", 22},

		// Drive Constants
		{"constant5", 3},
		{"constant6", -46},
		{"constant7", 23},
		{"constant8", 6},

		//Shooter Constants
		{"constant9", 7},
		{"constant10", 8}
};

void Constants::ReadFile()
{
	// get text file
	std::cout << "Reading constants" << std::endl;
	std::ifstream myfile("/home/lvuser/constants");

	// make a string to read into
	std::string line;

	// check if file actually exists
	if (!myfile.is_open())
	{
		DriverStation::ReportError("No Constants file found \n");
	}
	else
	{
		// read the file in line by line
		while (getline(myfile, line))
		{
			// find the name and value in the line
			int pos = line.find(':');
			std::string readName = line.substr (0, pos);
			float readValue = atof(line.substr(pos + 1).c_str());

			// search for the constant and override it
			for(int i = 0; i < NUM_CONST; i++)
			{
				if(ConstantsList[i].name == readName)
				{
					ConstantsList[i].value = readValue;
					DriverStation::ReportError("Overriding constant [" + readName + "] with [" + std::to_string(readValue) + "]\n");
				}
			}
		}

		// close the file
		myfile.close();
	}
}

float Constants::GetConstant(std::string constName)
{
	for(int i = 0; i < NUM_CONST; i++)
	{
		if(ConstantsList[i].name == constName)
		{
			return ConstantsList[i].value;
		}
	}

	return 0;
}
