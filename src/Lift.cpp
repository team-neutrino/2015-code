#include "Lift.h"
#include "Constants.h"
#include <stdlib.h>

Lift::Lift ():
		LiftMotor1(Constants::GetConstant("LiftMotor1Channel")),
		LiftMotor2(Constants::GetConstant("LiftMotor2Channel")),
		BeamBreak(Constants::GetConstant("BeamBreakChannel")),
		LimitSwitchBottom(Constants::GetConstant("LimitSwitchTopChannel")),
		LimitSwitchTop(Constants::GetConstant("LimitSwitchTopChannel")),
		IsLifting(false),
		OverrideEnabled(false)
{

}

void Lift::LevelSet(int levels)
{
	if (OverrideEnabled)
	{
		return;
	}

	IsLifting = true;

	for (int i = 0; i < levels; i++)
	{
		MoveLevel(true);
	}

	for (int i = 0; i > levels; i--)
	{
		MoveLevel(false);
	}

	if (!OverrideEnabled)
	{
		IsLifting = false;
	}
}

void Lift::MoveLevel(bool up)
{
	if (OverrideEnabled)
	{
		return;
	}

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

	// Runs the motor until we don't see the tape
	double startTime = GetTime();
	int BeamBreakCount = 0;
	while (BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) &&
			((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")) &&
			(!LimitSwitchTop.Get()) &&
			(!LimitSwitchBottom.Get()) &&
			(!OverrideEnabled))
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

	// Runs the motor until we see the tape
	startTime = GetTime();
	BeamBreakCount = 0;
	while (BeamBreakCount <= (Constants::GetConstant("LiftNumSamples")) &&
			((GetTime() - startTime) <= Constants::GetConstant("LiftTimeOut")) &&
			(!LimitSwitchTop.Get()) &&
			(!LimitSwitchBottom.Get()) &&
			(!OverrideEnabled))
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

	if (!OverrideEnabled)
	{
		LiftMotor1.Set(0);
		LiftMotor2.Set(0);
	}

}


void Lift::Reset()
{
	if(OverrideEnabled)
	{
		return;
	}

	IsLifting = true;

	LiftMotor1.Set(Constants::GetConstant("LiftMotorDownSpeed"));
	LiftMotor2.Set(Constants::GetConstant("LiftMotorDownSpeed"));

	double startTime = GetTime();
	while (!LimitSwitchBottom.Get() &&
			((GetTime() - startTime) <= Constants::GetConstant("LiftResetTimeOut")) &&
			(!OverrideEnabled))
	{

	}

	if(!OverrideEnabled)
	{
		LiftMotor1.Set(0);
		LiftMotor2.Set(0);
		IsLifting = false;
	}

	if ((GetTime() - startTime) >= Constants::GetConstant("LiftTimeOut"))
	{
		DriverStation::ReportError("Lift Reset Timeout\n");
	}


}


void Lift::ManualOverride(bool up)
{
	OverrideEnabled = true;
	IsLifting = true;

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

}

void Lift::EndManualOverride()
{
	if (OverrideEnabled)
	{
		OverrideEnabled = false;
		IsLifting = false;

		LiftMotor1.Set(0);
		LiftMotor2.Set(0);
	}
}

bool Lift::Lifting()
{
	return IsLifting;
}
