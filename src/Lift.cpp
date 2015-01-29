
#include "Lift.h"

Lift::Lift ():
		LiftMotor1(Constants::GetConstant("LiftMotor1Channel")),
		LiftMotor2(Constants::GetConstant("LiftMotor2Channel")),
		BeamBreak(Constants::GetConstant("BeamBreakSensor"))
{

}

void Lift::GoUp(int levels)
{
	while(BeamBreak.Get() )
	{
		LiftMotor1.Set(Constants::GetConstant("LiftMotorUpSpeed"));
		LiftMotor2.Set(Constants::GetConstant("LiftMotorUpSpeed"));
	}

	int BeamBreakCount = 0;
	while(BeamBreakCount <= 5)
	{
		if (BeamBreak.Get())
		{
			BeamBreakCount++;
		}
		LiftMotor1.Set(Constants::GetConstant("LiftMotorUpSpeed"));
		LiftMotor2.Set(Constants::GetConstant("LiftMotorUpSpeed"));
	}

}

void Lift::GoDown(int levels)
{
/*
 * while(limit switch is not pressed)
 * {
 * 		Both motors spin backward and it goes down
 * }
 */
}

int Lift::GetLevel()
{

	return 0;
}

bool Lift::Lifting()
{

	return true;
}
