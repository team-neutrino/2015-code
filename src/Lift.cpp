
#include "Lift.h"

Lift::Lift ():
		LiftMotor1(Constants::GetConstant("LiftMotor1Channel")),
		LiftMotor2(Constants::GetConstant("LiftMotor2Channel")),
		BeamBreak(Constants::GetConstant("BeamBreakSensor")),
		LimitSwitch(Constants::GetConstant("LimitSwitchSensor"))
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
	levels++;

}

void Lift::GoDown(int levels)
{

  while(!LimitSwitch.Get())
  {
 		LiftMotor1.Set(Constants::GetConstant("LiftMotorDownSpeed"));
 		LiftMotor2.Set(Constants::GetConstant("LiftMotorDownSpeed"));
  }
  levels = 0;

}

int Lift::GetLevel()
{

	return 0;
}

bool Lift::Lifting()
{

	return true;
}
