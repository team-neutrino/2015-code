#include "Sucky.h"
#include "Constants.h"

Sucky::Sucky():
		SuckyMotorLeft(Constants::GetConstant("SuckyMotorLeftChannel")),
		SuckyMotorRight(Constants::GetConstant("SuckyMotorRightChannel")),
		SuckySolenoidOpen(Constants::GetConstant("SuckySuckyOpenChannel")),
		SuckySolenoidClose(Constants::GetConstant("SuckySuckyCloseChannel"))
{

}

void Sucky::SuckIn()
{
	SuckyMotorRight.Set(-Constants::GetConstant("SuckyMotorInSpeed"));
	SuckyMotorLeft.Set(Constants::GetConstant("SuckyMotorInSpeed"));
}

void Sucky::SpitOut()
{
	SuckyMotorRight.Set(Constants::GetConstant("SuckyMotorOutSpeed"));
	SuckyMotorLeft.Set(-Constants::GetConstant("SuckyMotorOutSpeed"));
}

void Sucky::SetLeft(double speed)
{
	SuckyMotorLeft.Set(speed);
}

void Sucky::SetRight(double speed)
{
	SuckyMotorRight.Set(-speed);
}

void Sucky::Stop()
{
	SuckyMotorRight.Set(0);
	SuckyMotorLeft.Set(0);
}

void Sucky::Open(bool open)
{
	SuckySolenoidOpen(open);
	SuckySolenoidClose(!open);
}
