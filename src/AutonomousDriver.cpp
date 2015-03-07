#include "AutonomousDriver.h"
#include "Constants.h"


AutonomousDriver::AutonomousDriver(Drive* driveinst):
		Gyroscope(Constants::GetConstant("GyroAnalogChannel")),
		Encode(Constants::GetConstant("Encoder1ChannelA"), Constants::GetConstant("Encoder1ChannelB"))
{
	DriveInst = driveinst;
}

void AutonomousDriver::TurnDegrees(float degrees)
{
	float movespeed = Constants::GetConstant("AutonMoveSpeed");

	if(degrees == 0)
	{
		return;
	}

	Gyroscope.Reset();
	DriveInst->SetLeft(movespeed * (abs(degrees) / degrees));
	DriveInst->SetRight(-movespeed * (abs(degrees) / degrees));

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
	float movespeed = Constants::GetConstant("AutonMoveSpeed");
	float tickPerFoot = Constants::GetConstant("EncoderTickPerFoot");

	DriveInst->SetLeft(movespeed * (abs(feet) / feet));
	DriveInst->SetRight(movespeed * (abs(feet) / feet));

	if(Constants::GetConstant("UseTime"))
	{
		Wait(feet*Constants::GetConstant("FeetToTimeRatio"));
	}
	else
	{
		Encode.Reset();
		while (abs(Encode.Get() / tickPerFoot) < abs(feet))
		{
			Wait(.001);
		}
	}
	DriveInst->SetLeft(0);
	DriveInst->SetRight(0);
}
