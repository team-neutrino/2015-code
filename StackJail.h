#include "WPILib.h"
#include "Constants.h"
#pragma once

class StackJail {
public:
	StackJail();
	// Toggles the gate open/closed
	void GateToggle(bool open);

private:
	Solenoid LeftGateOpen;
	Solenoid LeftGateClose;
	Solenoid RightGateOpen;
	Solenoid RightGateClose;
};
