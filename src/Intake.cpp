#include <Intake.h>
#include "Constants.h"

Intake::Intake():
		SuckyMotorLeft(Constants::GetConstant("SuckyMotorLeftChannel")),
		SuckyMotorRight(Constants::GetConstant("SuckyMotorRightChannel")),
		SuckySolenoidOpen(Constants::GetConstant("SuckySolenoidOpenChannel")),
		SuckySolenoidClose(Constants::GetConstant("SuckySolenoidCloseChannel"))
{

}

void Intake::SuckIn()
{
	SuckyMotorRight.Set(Constants::GetConstant("SuckyMotorInSpeed"));
	SuckyMotorLeft.Set(-Constants::GetConstant("SuckyMotorInSpeed"));
}

void Intake::SpitOut()
{
	SuckyMotorRight.Set(-Constants::GetConstant("SuckyMotorOutSpeed"));
	SuckyMotorLeft.Set(Constants::GetConstant("SuckyMotorOutSpeed"));
}

void Intake::SetLeft(double speed)
{
	SuckyMotorLeft.Set(-speed);
}

void Intake::SetRight(double speed)
{
	SuckyMotorRight.Set(speed);
}

void Intake::Stop()
{
	SuckyMotorRight.Set(0);
	SuckyMotorLeft.Set(0);
}

void Intake::Open(bool open)
{
	SuckySolenoidOpen.Set(open);
	SuckySolenoidClose.Set(!open);
}
