
#include "WPILib.h"
#pragma once

class Lift
{
public:
	Lift ();
	void GoUp(int levels);
	void GoDown(int levels);
	void Reset();
	int GetLevels();
	bool Lifting();

private:
	Talon LiftMotor1;
	Talon LiftMotor2;
	DigitalInput BeamBreak;
	DigitalInput LimitSwitch;
	int CurrentLevel;
};






