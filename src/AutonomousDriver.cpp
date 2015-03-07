#include "AutonomousDriver.h"
#include "Constants.h"


AutonomousDriver::AutonomousDriver(Drive* driveinst)
//		Gyroscope(1)

{
	DriveInst = driveinst;
}

void AutonomousDriver::TurnDegrees(float degrees)
{
	int error = 20;
//	Gyroscope.Reset();
	if (degrees >= 0)
	{
		DriveInst->SetLeft(-1);
		DriveInst->SetRight(1);

	}
	else if (degrees <= 0)
	{
		DriveInst->SetLeft(1);
		DriveInst->SetRight(-1);
	}
//	while(Gyroscope.GetAngle() < degrees + error && Gyroscope.GetAngle() > degrees - error)
//	{
//		Wait(.01);
//	}
	DriveInst->SetLeft(0);
	DriveInst->SetRight(0);
}

void AutonomousDriver::MoveDistance(float feet)
{

}

void AutonomousDriver::FeetMoved(float feetmoved)
{

}
