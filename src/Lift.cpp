#include "Lift.h"
#include "Constants.h"
#include <stdlib.h>

Lift::Lift ():
		LiftMotor1(Constants::GetConstant("LiftMotor1Channel")),
		LiftMotor2(Constants::GetConstant("LiftMotor2Channel")),
		BeamBreak(Constants::GetConstant("BeamBreakChannel")),
		LimitSwitch(Constants::GetConstant("LimitSwitchChannel")),
		CurrentLevel(0)
{

}

void Lift::GoUp(int levels)
{
	if (CurrentLevel >= Constants::GetConstant("LiftMaxLevel"))
	{
		return;
	}

	LiftMotor1.Set(Constants::GetConstant("LiftMotorUpSpeed"));
	LiftMotor2.Set(-Constants::GetConstant("LiftMotorUpSpeed"));

	//Runs the motor until we don't see the tape
	double startTime = GetTime();
	int BeamBreakCount = 0;
	while(BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) && ((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")))
	{
		if (!BeamBreak.Get())
		{
			BeamBreakCount++;
		}
		else
		{
			BeamBreakCount = 0;
		}
		Wait(Constants::GetConstant("LiftSampleRate"));
	}
	if ((GetTime() - startTime) >= Constants::GetConstant("LiftTimeOut"))
	{
		DriverStation::ReportError("Lift Timeout: 1\n");
	}

	//Runs the motor until we see the tape
	startTime = GetTime();
	BeamBreakCount = 0;
	while(BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) && ((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")))
	{
		if (BeamBreak.Get())
		{
			BeamBreakCount++;
		}
		else
		{
			BeamBreakCount = 0;
		}
		Wait(Constants::GetConstant("LiftSampleRate"));

	}
	if ((GetTime() - startTime) >= Constants::GetConstant("LiftTimeOut"))
	{
		DriverStation::ReportError("Lift Timeout: 2\n");
	}
	LiftMotor1.Set(0);
	LiftMotor2.Set(0);

	CurrentLevel++;
}

/*void Lift::GoDown(int levels)
{
	LiftMotor1.Set(Constants::GetConstant("LiftMotorDownSpeed"));
	LiftMotor2.Set(-Constants::GetConstant("LiftMotorDownSpeed"));

	double startTime = GetTime();

	//Runs the motor until we don't see the tape
	int BeamBreakCount = 0;
	while(BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) && ((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")))
	{
		if (!BeamBreak.Get())
		{
			BeamBreakCount++;
		}
		else
		{
			BeamBreakCount = 0;
		}
		Wait(Constants::GetConstant("LiftSampleRate"));
	}
	if ((GetTime() - startTime) >= Constants::GetConstant("LiftTimeOut"))
	{
		DriverStation::ReportError("Lift Timeout: 1\n");
	}

	//Runs the motor until we see the tape
	startTime = GetTime();
	BeamBreakCount = 0;
	while(BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) && ((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")))
	{
		if (BeamBreak.Get())
		{
			BeamBreakCount++;
		}
		else
		{
			BeamBreakCount = 0;
		}
		Wait(Constants::GetConstant("LiftSampleRate"));

	}
	if ((GetTime() - startTime) >= Constants::GetConstant("LiftTimeOut"))
	{
		DriverStation::ReportError("Lift Timeout: 2\n");
	}
	LiftMotor1.Set(0);
	LiftMotor2.Set(0);

	CurrentLevel++;
}
*/
// This c
void Lift::Reset()
{
	double startTime = GetTime();
	while(!LimitSwitch.Get() && ((GetTime() - startTime) <= Constants::GetConstant("LiftResetTimeOut")))
	{
 		LiftMotor1.Set(Constants::GetConstant("LiftMotorDownSpeed"));
 		LiftMotor2.Set(Constants::GetConstant("LiftMotorDownSpeed"));
	}

  CurrentLevel = 0;

}

int Lift::GetLevels()
{
	return CurrentLevel;
}

bool Lift::Lifting()
{

	return true;
}
