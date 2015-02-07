#include "Sucky.h"
#include "Constants.h"

Sucky::Sucky():
		SuckyMotorLeft(Constants::GetConstant("SuckyMotorLeftChannel")),
		SuckyMotorRight(Constants::GetConstant("SuckyMotorRightChannel"))
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

void Sucky::Stop()
{
	SuckyMotorRight.Set(0);
	SuckyMotorLeft.Set(0);
}
