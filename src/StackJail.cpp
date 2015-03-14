#include <StackJail.h>

StackJail::StackJail():
	GateOpen(Constants::GetConstant("StackJailSolenoidOpen")),
	GateClose(Constants::GetConstant("StackJailSolenoidClose"))
{

}
void StackJail::GateToggle(bool open)
{
	GateOpen.Set(open);
	GateClose.Set(!open);
}
