
#include "WPILib.h"
#pragma once

class Lift
{
public:
	Lift ();
	void LevelSet(int levels);
	void Reset();
	bool Lifting();

private:
	Talon LiftMotor1;
	Talon LiftMotor2;
	DigitalInput BeamBreak;
	DigitalInput LimitSwitchBottom;
	DigitalInput LimitSwitchTop;
	void MoveLevel(bool up);
	bool IsLifting;
};






