
#include "Lift.h"

Lift::Lift ():
		LiftMotor1(Constants::GetConstant("LiftMotor1Channel")),
		LiftMotor2(Constants::GetConstant("LiftMotor2Channel"))
{

}

void Lift::GoUp(int levels)
{

}

void Lift::GoDown(int levels)
{

}

int Lift::GetLevel()
{

	return 0;
}

bool Lift::Lifting()
{

	return true;
}
