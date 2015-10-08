#include "CanGrabberArm.h"

CanGrabberArm::CanGrabberArm():
	ToggleUp(Constants::GetConstant("DeadSpiderUp")),
	ToggleDown(Constants::GetConstant("DeadSpiderDown"))
{

}

void CanGrabberArm::CanGrabberToggle(bool on)
{
	ToggleUp.Set(on);
	ToggleDown.Set(!on);
}
