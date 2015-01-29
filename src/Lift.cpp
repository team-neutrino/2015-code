
#include "Lift.h"

Lift::Lift ():
		LiftMotor1(Constants::GetConstant("LiftMotor1Channel")),
		LiftMotor2(Constants::GetConstant("LiftMotor2Channel")),
		BeamBreak(Constants::GetConstant("BeamBreakSensor"))
{

}

void Lift::GoUp(int levels)
{
	int beamBreakCount = 0;
	while(beamBreakCount <= 3 && )
	{
		if (!BeamBreak.Get())
		{
			beamBreakCount++;
		}
		LiftMotor1.Set(Constants::GetConstant("LiftMotorUpSpeed"));
		LiftMotor2.Set(Constants::GetConstant("LiftMotorUpSpeed"));
	}

	while(!BeamBreak.Get())
	{
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
