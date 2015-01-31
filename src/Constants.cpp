#include "Constants.h"
#include "WPILib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

Constants::Constant Constants::ConstantsList[NUM_CONST] =
{
		// Drive Constants
		{"DriveLeft1Channel", 0},
		{"DriveLeft2Channel", 1},
		{"DriveRight1Channel", 2},
		{"DriveRight2Channel", 3},

		// Lift Constants
		{"LiftMotor1Channel", 1},
		{"LiftMotor2Channel", 2},

		{"LiftMotorUpSpeed", 0.5},
		{"LiftMotorDownSpeed", 0.5},

		{"BeamBreakChannel", 9},
		{"LimitMotorChannel", 7},

		{"LiftTimeOut", 10},
		{"LiftSampleRate", 0.2},
		{"LiftNumSamples", 5},
		{"LiftResetTimeOut", 20},
		{"LiftMaxLevel", 5},

		//Sucky Constants
		{"SuckyMotorRightChannel", 4},
		{"SuckyMotorLeftChannel", 5},

		{"SuckyMotorInSpeed", 1},
		{"SuckyMotorOutSpeed", 1},
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
	} else
	{
		// read the file in line by line
		while (getline(myfile, line))
		{
			// find the name and value in the line
			int pos = line.find(':');
			std::string readName = line.substr(0, pos);
			float readValue = atof(line.substr(pos + 1).c_str());

			// make a flag to tell if the the constant actually exists
			bool constantFound = false;

			// search for the constant and override it
			for (int i = 0; i < NUM_CONST; i++)
			{
				if (ConstantsList[i].name == readName)
				{
					ConstantsList[i].value = readValue;
					DriverStation::ReportError(
							"Overriding constant [" + readName + "] with ["
									+ std::to_string(readValue) + "]\n");

					constantFound = true;
					break;
				}
			}

			// the constant in the text file doesn't exist
			if (!constantFound)
			{
				DriverStation::ReportError(
						"Can not override not existent constant [" + readName
								+ "]\n");
			}
		}

		// close the file
		myfile.close();
	}
}

float Constants::GetConstant(std::string constName)
{
	for (int i = 0; i < NUM_CONST; i++)
	{
		if (ConstantsList[i].name == constName)
		{
			return ConstantsList[i].value;
		}
	}

	DriverStation::ReportError(
			"No constant found with the name [" + constName + "]\n");
	return 0;
}
