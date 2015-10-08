#include <Intake.h>
#include "Constants.h"

Intake::Intake():
		IntakeMotorLeft(Constants::GetConstant("SuckyMotorLeftChannel")),
		IntakeMotorRight(Constants::GetConstant("SuckyMotorRightChannel")),
		IntakeSolenoidOpen(Constants::GetConstant("SuckySolenoidOpenChannel")),
		InakeSolenoidClose(Constants::GetConstant("SuckySolenoidCloseChannel"))
{

}

void Intake::SuckIn()
{
	IntakeMotorRight.Set(Constants::GetConstant("SuckyMotorInSpeed"));
	IntakeMotorLeft.Set(-Constants::GetConstant("SuckyMotorInSpeed"));
}

void Intake::SpitOut()
{
	IntakeMotorRight.Set(-Constants::GetConstant("SuckyMotorOutSpeed"));
	IntakeMotorLeft.Set(Constants::GetConstant("SuckyMotorOutSpeed"));
}

void Intake::SetLeft(double speed)
{
	IntakeMotorLeft.Set(-speed);
}

void Intake::SetRight(double speed)
{
	IntakeMotorRight.Set(speed);
}

void Intake::Stop()
{
	IntakeMotorRight.Set(0);
	IntakeMotorLeft.Set(0);
}

void Intake::Open(bool open)
{
	IntakeSolenoidOpen.Set(open);
	InakeSolenoidClose.Set(!open);
}
