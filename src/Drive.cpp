#include "Drive.h"
#include "Constants.h"

Drive::Drive():
		MotorLeft1(Constants::GetConstant("DriveLeft1Channel")),
		MotorLeft2(Constants::GetConstant("DriveLeft2Channel")),
		MotorRight1(Constants::GetConstant("DriveRight1Channel")),
		MotorRight2(Constants::GetConstant("DriveRight2Channel"))
{

}

void Drive::SetLeft(float speed)
{
	 MotorLeft1.Set(speed);
	 MotorLeft2.Set(speed);
}

void Drive::SetRight(float speed)
{
	MotorRight1.Set(-speed);
	MotorRight2.Set(-speed);
}
