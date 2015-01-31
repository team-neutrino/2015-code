#include "Lift.h"
#include "Constants.h"
#include <stdlib.h>

Lift::Lift ():
		LiftMotor1(Constants::GetConstant("LiftMotor1Channel")),
		LiftMotor2(Constants::GetConstant("LiftMotor2Channel")),
		BeamBreak(Constants::GetConstant("BeamBreakChannel")),
		LimitSwitch(Constants::GetConstant("LimitSwitchChannel")),
		IsLifting(false)
{

}

void Lift::LevelSet(int levels)
{

	IsLifting = true;

	for (int i = 0; i < levels; i++)
	{
		MoveLevel(true);
	}

	for (int i = 0; i > levels; i--)
	{
		MoveLevel(false);
	}

	IsLifting = false;
}

void Lift::MoveLevel(bool up)
{
	if (up)
	{
		LiftMotor1.Set(Constants::GetConstant("LiftMotorUpSpeed"));
		LiftMotor2.Set(-Constants::GetConstant("LiftMotorUpSpeed"));
	}
	else
	{
		LiftMotor1.Set(-Constants::GetConstant("LiftMotorDownSpeed"));
		LiftMotor2.Set(Constants::GetConstant("LiftMotorDownSpeed"));
	}

	//Runs the motor until we don't see the tape
	double startTime = GetTime();
	int BeamBreakCount = 0;
	while(BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) &&
			((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")) &&
			(!LimitSwitchTop.Get()) &&
			(!LimitSwitchBottom.Get()))
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
	while(BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) &&
			((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")) &&
			(!LimitSwitchTop.Get()) &&
			(!LimitSwitchBottom.Get()))
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
}


void Lift::Reset()
{
	IsLifting = true;

	double startTime = GetTime();

	while(!LimitSwitchBottom.Get() && ((GetTime() - startTime) <= Constants::GetConstant("LiftResetTimeOut")))
	{
 		LiftMotor1.Set(Constants::GetConstant("LiftMotorDownSpeed"));
 		LiftMotor2.Set(Constants::GetConstant("LiftMotorDownSpeed"));
	}
	LiftMotor1.Set(0);
	LiftMotor2.Set(0);

	if ((GetTime() - startTime) >= Constants::GetConstant("LiftTimeOut"))
	{
		DriverStation::ReportError("Lift Reset Timeout\n");
	}

	IsLifting = false;

}


bool Lift::Lifting()
{
	return IsLifting;
}
