#include "WPILib.h"
#pragma once

class Lift
{
public:
	Lift();

	/**
	 * Moves the lift up/down the specified amount of levels.
	 */
	void LevelChange(int levels);

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

	/**
	 * Disables Manual Override.
	 */
	void EndManualOverride();

private:
	Talon LiftMotor1;
	Talon LiftMotor2;
	DigitalInput BeamBreak;
	DigitalInput LimitSwitchBottom;
	DigitalInput LimitSwitchTop;

	const char RESET = 100;

	bool IsLifting;
	bool OverrideEnabled;
	char CurrentTask;

	std::thread LiftThread;
	std::thread MonitorThread;

	void resetThreaded();
	void levelChangeThreaded(int levels);
	void moveLevelThreaded(bool up);
	void lifterThread();
	void monitorThread();
};
