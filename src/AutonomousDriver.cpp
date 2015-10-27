#include "AutonomousDriver.h"
#include "Constants.h"
#include "WPILib.h"
#include <cmath>


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
	DriveInst->SetLeft(movespeed * (std::abs(degrees) / degrees));
	DriveInst->SetRight(-movespeed * (std::abs(degrees) / degrees));

	while (std::abs(Gyroscope.GetAngle()) < std::abs(degrees) && DriverStation::GetInstance()->IsAutonomous())
	{
		std::cout << Gyroscope.GetAngle() << '\n';
		Wait(.001);
	}

	DriveInst->SetLeft(0);
	DriveInst->SetRight(0);
	std::cout << Gyroscope.GetAngle() << '\n';
}

void AutonomousDriver::MoveDistance(float feet, float spd)
{
	float movespeed = Constants::GetConstant("AutonMoveSpeed") * spd;
	float tickPerFoot = Constants::GetConstant("EncoderTickPerFoot");
	DriverStation::ReportError("Motors should start\n");
	DriveInst->SetLeft(movespeed * (abs(feet) / feet));
	DriveInst->SetRight(movespeed * (.95) * (abs(feet) / feet));
	DriverStation::ReportError("Motors have started\n");

	if(Constants::GetConstant("UseTime"))
	{
		Wait(feet*Constants::GetConstant("FeetToTimeRatio"));
	}
	else
	{
		Encode.Reset();
		while (std::abs(Encode.Get() / tickPerFoot) < abs(feet) && DriverStation::GetInstance()->IsAutonomous())
		{
			std::cout << std::abs((float)Encode.Get() / tickPerFoot) << "," << Encode.Get() << "\n";
			Wait(.001);
		}
	}
	DriverStation::ReportError("Motors should stop here\n");
	DriveInst->SetLeft(0);
	DriveInst->SetRight(0);
	DriverStation::ReportError("Motors are stopped\n");
}

void AutonomousDriver::MoveForTime(float time)
{
	float movespeed = Constants::GetConstant("AutonMoveSpeed");

	if (time >= 0)
	{
		DriveInst->SetLeft(movespeed);
		DriveInst->SetRight(movespeed);
		Wait (std::abs(time));
		DriveInst->SetLeft(0);
		DriveInst->SetRight(0);
	}
	else if (time <= 0)
	{
		DriveInst->SetLeft(-movespeed);
		DriveInst->SetRight(-movespeed);
		Wait (std::abs(time));
		DriveInst->SetLeft(0);
		DriveInst->SetRight(0);
	}
	else
	{
		DriveInst->SetLeft(0);
		DriveInst->SetRight(0);
	}
}
