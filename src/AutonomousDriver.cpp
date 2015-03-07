#include "AutonomousDriver.h"
#include "Constants.h"


AutonomousDriver::AutonomousDriver(Drive* driveinst):
		Gyroscope(Constants::GetConstant("GyroAnalogChannel"))
{
	DriveInst = driveinst;
}

void AutonomousDriver::TurnDegrees(float degrees)
{
	if(degrees == 0)
	{
		return;
	}

	Gyroscope.Reset();
	DriveInst->SetLeft(-.4 * (abs(degrees) / degrees));
	DriveInst->SetRight(.4 * (abs(degrees) / degrees));

	while (abs(Gyroscope.GetAngle()) < abs(degrees))
	{
		std::cout << Gyroscope.GetAngle() << '\n';
		Wait(.001);
	}

	DriveInst->SetLeft(0);
	DriveInst->SetRight(0);
	std::cout << Gyroscope.GetAngle() << '\n';
}

void AutonomousDriver::MoveDistance(float feet)
{
	if(Constants::GetConstant("UseTime"))
	{
		Wait(feet*Constants::GetConstant("FeetToTimeRatio"));
	}
	else
	{
		//TODO implement encoder
	}
}
