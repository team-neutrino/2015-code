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
	std::thread LiftThread;
	void resetCalledByThread();
	void levelChangeCalledByThread(int levels);
	void moveLevel(bool up);
	bool IsLifting;
	bool OverrideEnabled;
	void liftThreadRunnable();
	int CurrentTask;

};
