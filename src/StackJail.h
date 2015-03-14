#include "WPILib.h"
#include "Constants.h"
#pragma once

class StackJail {
public:
	StackJail();
	// Toggles the gate open/closed
	void GateToggle(bool open);

private:
	Solenoid GateOpen;
	Solenoid GateClose;
//	Solenoid RightGateOpen;
//	Solenoid RightGateClose;
};
