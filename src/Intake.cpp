#include <Intake.h>
#include "Constants.h"

Intake::Intake():
		IntakeMotorLeft(Constants::GetConstant("IntakeMotorLeftChannel")),
		IntakeMotorRight(Constants::GetConstant("IntakeMotorRightChannel")),
		IntakeSolenoidOpen(Constants::GetConstant("IntakeSolenoidOpenChannel")),
		InakeSolenoidClose(Constants::GetConstant("IntakeSolenoidCloseChannel"))
{

}

void Intake::SuckIn()
{
	IntakeMotorRight.Set(Constants::GetConstant("IntakeMotorInSpeed"));
	IntakeMotorLeft.Set(-Constants::GetConstant("IntakeMotorInSpeed"));
}

void Intake::SpitOut()
{
	IntakeMotorRight.Set(-Constants::GetConstant("IntakeMotorOutSpeed"));
	IntakeMotorLeft.Set(Constants::GetConstant("IntakeMotorOutSpeed"));
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
