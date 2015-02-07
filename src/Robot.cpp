#include "WPILib.h"
#include "Lift.h"
#include "Constants.h"
#include "AutonomousSwitcher.h"
#include "Drive.h"
#include "Sucky.h"

class Robot: public SampleRobot
{

public:
	AutonomousSwitcher AutoSwitch;
	Joystick JoyRight;
	Joystick JoyLeft;
	Joystick Gamepad;
	Drive DriveInst;
	Lift LiftInst;
	Sucky SuckyInst;

	/**
	 * Constructor
	 */
	Robot():
		AutoSwitch(),
		JoyRight(Constants::GetConstant("JoyRightPort")),
		JoyLeft(Constants::GetConstant("JoyLeftPort")),
		Gamepad(Constants::GetConstant("GamepadPort")),
		DriveInst(),
		LiftInst(),
		SuckyInst()
	{

	}

	/**
	 * Robot Initialization
	 */
	void RobotInit()
	{
		Constants::ReadFile();
	}

	/**
	 * Disabled mode
	 */
	void Disabled()
	{

	}

	/**
	 * Autonomous mode
	 */
	void Autonomous()
	{
		AutoSwitch.RunAuto();
	}

	/**
	 * Operator Control mode
	 */
	void OperatorControl()
	{
		float driveSlowMultiplier = Constants::GetConstant("DriveSlowMultiplier");
		float driveFastMultiplier = Constants::GetConstant("DriveFastMultiplier");
		float driveMultiplier = driveFastMultiplier;

		while(IsOperatorControl() && IsEnabled())
		{
			// Drive Controls
			driveMultiplier =(JoyLeft.GetRawButton(1) || JoyRight.GetRawButton(1)) ?
								driveFastMultiplier : driveSlowMultiplier;
			DriveInst.SetLeft(-JoyLeft.GetY() * fabs(JoyLeft.GetY()) * driveMultiplier);
			DriveInst.SetRight(JoyRight.GetY() * fabs(JoyRight.GetY()) * driveMultiplier);

			// Lift Controls
			if (Gamepad.GetRawButton(5))
			{
				SuckyInst.SuckIn();
			}
			else if (Gamepad.GetRawButton(6))
			{
				SuckyInst.SpitOut();
			}

			// Sucky Controls
			if (Gamepad.GetRawButton(4))
			{
				LiftInst.ManualOverride(true);
			}
			else if (Gamepad.GetRawButton(1))
			{
				LiftInst.ManualOverride(false);
			}

			Wait(.001);
		}
	}

	/**
	 * Test mode
	 */
	void Test()
	{

	}
};

START_ROBOT_CLASS(Robot);
