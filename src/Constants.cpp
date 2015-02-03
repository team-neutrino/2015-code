#include "Constants.h"
#include "WPILib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

Constants::Constant Constants::ConstantsList[NUM_CONST] =
{
	//Autonomous Constants
	{"AutonSwitchInput0Channel", 0},
	{"AutonSwitchInput1Channel", 1},
	{"AutonSwitchInput2Channel", 2},
	{"AutonSwitchInput3Channel", 3},

	// Drive Constants
	{"DriveLeft1Channel", 0},
	{"DriveLeft2Channel", 1},
	{"DriveRight1Channel", 2},
	{"DriveRight2Channel", 3},

	// Lift Constants
	{"LiftMotor1Channel", 4},
	{"LiftMotor2Channel", 5},

	{"LiftMotorUpSpeed", 0.5},
	{"LiftMotorDownSpeed", 0.5},

	{"BeamBreakChannel", 4},
	{"LimitSwitchTopChannel", 5},
	{"LimitSwitchBottomChannel", 6},

	{"LiftTimeOut", 10},
	{"LiftSampleRate", 0.01},
	{"LiftNumSamples", 5},
	{"LiftResetTimeOut", 5},

	//Sucky Constants
	{"SuckyMotorRightChannel", 6},
	{"SuckyMotorLeftChannel", 7},

	{"SuckyMotorInSpeed", 1},
	{"SuckyMotorOutSpeed", 1}
};

/**
 * Attempts to override constant with name and value in the given string.
 * Prints an error to the driver station if constant doesn't exist.
 */
void Constants::override_const(std::string line) {
	// find the name and value in the line
	int pos = line.find(':');
	std::string readName = line.substr(0, pos);
	float readValue = atof(line.substr(pos + 1).c_str());

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

	// print error if constant in text file doesn't exist
	if (!constantFound)
	{
		DriverStation::ReportError(
				"Can not override not existent constant [" + readName
						+ "]\n");
	}
}

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
		DriverStation::ReportError("No Constants file found\n");
	}
	else
	{
		// read the file in line by line
		while (getline(myfile, line))
		{
			override_const(line);
		}

		// close the file
		myfile.close();
	}
}

float Constants::GetConstant(std::string constName)
{
	float ret = 0;
	for (int i = 0; i < NUM_CONST; i++)
	{
		if (ConstantsList[i].name == constName)
		{
			ret = ConstantsList[i].value;
			break;
		}
	}

	DriverStation::ReportError(
			"No constant found with the name [" + constName + "]\n");
	return ret;
}
