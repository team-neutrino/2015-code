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

void AutonomousDriver::MoveDistance(float feet, float spd)
{
	float movespeed = Constants::GetConstant("AutonMoveSpeed") * spd;
	float tickPerFoot = Constants::GetConstant("EncoderTickPerFoot");
	DriverStation::ReportError("Motors should start\n");
	DriveInst->SetLeft(movespeed * (abs(feet) / feet));
	DriveInst->SetRight(movespeed * 1.1 * (abs(feet) / feet));
	DriverStation::ReportError("Motors have started\n");

	if(Constants::GetConstant("UseTime"))
	{
		Wait(feet*Constants::GetConstant("FeetToTimeRatio"));
	}
	else
	{
		Encode.Reset();
		while (abs(Encode.Get() / tickPerFoot) < abs(feet))
		{
//			float encoderout = Encode.Get();
//			char tmpStr[50];
//			sprintf(tmpStr, "%f\n", encoderout);
//			std::string tmp = std::string(tmpStr);
//			DriverStation::ReportError(tmpStr);

			Wait(.001);
		}
	}
	DriverStation::ReportError("Motors should stop here\n");
	DriveInst->SetLeft(0);
	DriveInst->SetRight(0);
	DriverStation::ReportError("Motors are stopped\n");
}
