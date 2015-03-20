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
	{"AutonSwitchInput0Channel", 4},
	{"AutonSwitchInput1Channel", 5},
	{"AutonSwitchInput2Channel", 6},
	{"AutonSwitchInput3Channel", 7},
	{"GyroAnalogChannel", 1},
	{"Encoder1ChannelA", 8},
	{"Encoder1ChannelB", 9},
	{"UseTime", 0},
	{"FeetToTimeRatio", .55},
	{"EncoderTickPerFoot", 1500},
	{"AutonMoveSpeed", .45},

	// Controllers
	{"JoyRightPort", 1},
	{"JoyLeftPort", 0},
	{"GamepadPort", 2},

	// Button Mapping - Joysticks
	{"SpeedBoostButton", 1},
	{"JoyLiftResetButton", 2},

	// Button Mapping - Gamepad
	{"SuckyXAxis", 0},
	{"SuckyYAxis", 1},
	{"SpitOutButton", 6},
	{"SuckyOpenButton", 5},

	{"LiftUpButton", 4},
	{"LiftDownButton", 1},
	{"LiftResetButton", 3},
	{"LiftOverrideTrigger", 3},
	{"LiftAutoStackButton", 2},

	// Drive Constants
	{"DriveLeft1Channel", 1},
	{"DriveLeft1PowerChannel", 15},
	{"DriveLeft2Channel", 2},
	{"DriveLeft2PowerChannel", 14},
	{"DriveRight1Channel", 5},
	{"DriveRight1PowerChannel", 3},
	{"DriveRight2Channel", 6},
	{"DriveRight2PowerChannel", 0},

	{"DriveSlowMultiplier", .5},
	{"DriveFastMultiplier", 1},

	// Lift Constants
	{"LiftMotor1Channel", 4},
	{"LiftMotor1PowerChannel", 8},
	{"LiftMotor2Channel", 8},
	{"LiftMotor2PowerChannel", 7},

	{"LiftMotorUpOverideSpeed", .5},
	{"LiftMotorDownOverideSpeed", .5},

	{"LiftMotorUpSpeed", 1},
	{"LiftMotorDownSpeed", .6},

	{"BeamBreakChannel", 0},
	{"LimitSwitchTopChannel", 2},
	{"LimitSwitchBottomChannel", 3},

	{"LiftTimeOut", 3},
	{"LiftSampleRate", 0.001},
	{"LiftNumSamples", 5},
	{"LiftResetTimeOut", 3},

	{"LiftThreadWaitTime", 0.05},

	//Sucky Constants
	{"SuckyMotorRightChannel", 7},
	{"SuckyMotorRightPowerChannel", 11},
	{"SuckyMotorLeftChannel", 3},
	{"SuckyMotorLeftPowerChannel", 7},

	{"SuckyMotorInSpeed", .75},
	{"SuckyMotorOutSpeed", .75},

	{"SuckySolenoidOpenChannel", 0},
	{"SuckySolenoidCloseChannel", 1},

	//StackJail Constants
	{"StackJailSolenoidOpen", 2},
	{"StackJailSolenoidClose", 3},

	//Lights Constants
	{"LightsChannel1", 0},
	{"LightsChannel2", 0},
	{"LightsChannel3", 0},

	//Misc Constants
	{"PdpAttached", 1}
};

Constants::Constants()
{
	ReadFile();
}

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
