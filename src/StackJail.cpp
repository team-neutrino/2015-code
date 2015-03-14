#include <StackJail.h>

StackJail::StackJail():
	GateOpen(Constants::GetConstant("StackJailSolenoidOpen")),
	GateClose(Constants::GetConstant("StackJailSolenoidClose"))
//	RightGateOpen(Constants::GetConstant("StackJailRightSolenoidOpen")),
//	RightGateClose(Constants::GetConstant("StackJailRightSolenoidClose"))
{

}
void StackJail::GateToggle(bool open)
{
	GateOpen.Set(open);
//	RightGateOpen.Set(open);
	GateClose.Set(!open);
//	RightGateClose.Set(!open);
}
