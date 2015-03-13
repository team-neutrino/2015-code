#include "StackJail.h"

StackJail::StackJail():
	LeftGateOpen(Constants::GetConstant("StackJailLeftSolenoidOpen")),
	LeftGateClose(Constants::GetConstant("StackJailLeftSolenoidClose")),
	RightGateOpen(Constants::GetConstant("StackJailRightSolenoidOpen")),
	RightGateClose(Constants::GetConstant("StackJailRightSolenoidClose"))
{

}
void StackJail::GateToggle(bool open)
{
	LeftGateOpen.Set(open);
	RightGateOpen.Set(open);
	LeftGateClose.Set(!open);
	RightGateClose.Set(!open);
}
