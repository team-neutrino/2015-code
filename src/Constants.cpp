#include "Constants.h"
#include "WPILib.h"
#include "DriverOutputs.h"
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

	{"LiftThreadWaitTime", 0.05},

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
void Constants::overrideConst(std::string line) {
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
			DriverOutputs::ReportError(
					"Overriding constant [" + readName + "] with ["
							+ std::to_string(readValue) + "]");

			constantFound = true;
			break;
		}
	}

	// print error if constant in text file doesn't exist
	if (!constantFound)
	{
		DriverOutputs::ReportError(
				"Can not override not existent constant [" + readName
						+ "]");
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
		DriverOutputs::ReportError("No Constants file found");
	}
	else
	{
		// read the file in line by line
		while (getline(myfile, line))
		{
			overrideConst(line);
		}

		// close the file
		myfile.close();
	}
}

float Constants::GetConstant(std::string constName)
{
	float ret = 0;
	bool ConstantFound = false;
	for (int i = 0; i < NUM_CONST; i++)
	{
		if (ConstantsList[i].name == constName)
		{
			ret = ConstantsList[i].value;
			ConstantFound = true;
			break;
		}
	}
	if(!ConstantFound)
	{
		DriverOutputs::ReportError(
			"No constant found with the name [" + constName + "]");
	}

	return ret;
}
