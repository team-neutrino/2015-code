#include "WPILib.h"
#include "Constants.h"
#pragma once

class CanGrabberArm {
public:
	CanGrabberArm();

	void CanGrabberToggle(bool on);
private:
	Solenoid ToggleUp;
	Solenoid ToggleDown;
};

