#include <StackJail.h>

StackJail::StackJail():
	gateOpen(Constants::GetConstant("StackJailSolenoidOpen")),
	gateClose(Constants::GetConstant("StackJailSolenoidClose")),
	Gamepad(Constants::GetConstant("GamepadPort"))
{

}
void StackJail::GateToggle(bool open)
{
	gateOpen.Set(open);
	gateClose.Set(!open);
}
