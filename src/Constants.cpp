#include "Constants.h"
#include "WPILib.h"
#include "DriverOutputs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

Constants::Constant Constants::ConstantsList[NUM_CONST] =
{
	// Autonomous Constants
	{"AutonSwitchInput0Channel", 0},
	{"AutonSwitchInput1Channel", 1},
	{"AutonSwitchInput2Channel", 2},
	{"AutonSwitchInput3Channel", 3},

	// Controllers
	{"JoyRightPort", 1},
	{"JoyLeftPort", 0},
	{"GamepadPort", 2},

	// Button Mapping - Joysticks
	{"SpeedBoostButton", 1},
	{"JoyLiftResetButton", 2},

	// Button Mapping - Gamepad
	{"SuckInButton", 5},
	{"SpitOutButton", 6},

	{"LiftUpButton", 4},
	{"LiftDownButton", 1},
	{"LiftResetButton", 3},
	{"LiftOverrideButton", 10},

	// Drive Constants
	{"DriveLeft1Channel", 1},
	{"DriveLeft1PowerChannel", 0}, //TODO
	{"DriveLeft2Channel", 2},
	{"DriveLeft2PowerChannel", 1}, //TODO
	{"DriveRight1Channel", 5},
	{"DriveRight1PowerChannel", 2}, //TODO
	{"DriveRight2Channel", 6},
	{"DriveRight2PowerChannel", 3}, //TODO

	{"DriveSlowMultiplier", .5},
	{"DriveFastMultiplier", 1},

	// Lift Constants
	{"LiftMotor1Channel", 0},
	{"LiftMotor1PowerChannel", 4}, //TODO
	{"LiftMotor2Channel", 8},
	{"LiftMotor2PowerChannel", 5}, //TODO

	{"LiftMotorUpOverideSpeed", .5},
	{"LiftMotorDownOverideSpeed", .5},

	{"LiftMotorUpSpeed", 1},
	{"LiftMotorDownSpeed", 1},

	{"BeamBreakChannel", 4},
	{"LimitSwitchTopChannel", 5},
	{"LimitSwitchBottomChannel", 6},

	{"LiftTimeOut", 10},
	{"LiftSampleRate", 0.01},
	{"LiftNumSamples", 5},
	{"LiftResetTimeOut", 5},

	{"LiftThreadWaitTime", 0.05},

	//Sucky Constants
	{"SuckyMotorRightChannel", 7},
	{"SuckyMotorRightPowerChannel", 6}, //TODO
	{"SuckyMotorLeftChannel", 3},
	{"SuckyMotorLeftPowerChannel", 7}, //TODO

	{"SuckyMotorInSpeed", 1},
	{"SuckyMotorOutSpeed", 1},

	//Misc Constants
	{"PdpAttached", 1}
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
