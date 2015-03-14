#include "WPILib.h"
#include "StackJail.h"
#pragma once

class Lift
{
public:
	Lift();

	/**
	 * Moves the lift up/down the specified amount of levels.
	 */
	void LevelChange(signed char levels);

	/**
	 * Moves the lift to its bottom-most level.
	 */
	void Reset();

	/**
	 * Returns whether or not the robot is currently lifting.
	 */
	bool Lifting();

	/**
	 * Moves the lift up/down unconditionally until EndManualOverride is called
	 * (ignores LevelSet and Reset calls).
	 */
	void ManualOverride(bool up);

	//TODO Reimplement this in a better way
	void ManualOverrideStopped();

	/**
	 * Disables Manual Override.
	 */
	void EndManualOverride();

	void WaitForLift();

private:
	Talon LiftMotor1;
	Talon LiftMotor2;
	DigitalInput BeamBreak;
	DigitalInput LimitSwitchBottom;
	DigitalInput LimitSwitchTop;
	StackJail jail;

	signed const char RESET = 100;

	bool IsLifting;
	bool OverrideEnabled;
	signed char CurrentTask;

	std::thread LiftThread;
	std::thread MonitorThread;

	void resetThreaded();
	void levelChangeThreaded(int levels);
	void moveLevelThreaded(bool up);
	void lifterThread();
	void monitorThread();
};
