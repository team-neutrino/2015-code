#include "WPILib.h"
#include "Lift.h"
#include "Constants.h"
#include "AutonomousSwitcher.h"
#include "Drive.h"
#include "Sucky.h"
#include "DriverOutputs.h"

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

		int speedBoostButton = Constants::GetConstant("SpeedBoostButton");

		int suckInButton = Constants::GetConstant("SuckInButton");
		int spitOutButton = Constants::GetConstant("SpitOutButton");

		int liftUpButton = Constants::GetConstant("LiftUpButton");
		int liftDownButton = Constants::GetConstant("LiftDownButton");
		int liftResetButton = Constants::GetConstant("LiftResetButton");
		int liftOverrideButton = Constants::GetConstant("LiftOverrideButton");

		while(IsOperatorControl() && IsEnabled())
		{
			// Drive Controls
			driveMultiplier =(JoyLeft.GetRawButton(speedBoostButton) || JoyRight.GetRawButton(speedBoostButton)) ?
								driveFastMultiplier : driveSlowMultiplier;
			DriveInst.SetLeft(-JoyLeft.GetY() * fabs(JoyLeft.GetY()) * driveMultiplier);
			DriveInst.SetRight(JoyRight.GetY() * fabs(JoyRight.GetY()) * driveMultiplier);

			// Lift Controls
			if (Gamepad.GetRawButton(suckInButton))
			{
				SuckyInst.SuckIn();
			}
			else if (Gamepad.GetRawButton(spitOutButton))
			{
				SuckyInst.SpitOut();
			}
			else
			{
				SuckyInst.Stop();
			}

			// Sucky Controls
			if (!Gamepad.GetRawButton(liftOverrideButton))
			{
				// Normal Control
				if(!LiftInst.Lifting())
				{
					if (Gamepad.GetRawButton(liftUpButton))
					{
						LiftInst.LevelChange(1);
					}
					else if (Gamepad.GetRawButton(liftDownButton))
					{
						LiftInst.LevelChange(-1);
					}
					else if (Gamepad.GetRawButton(liftResetButton))
					{
						LiftInst.Reset();
					}
				}
			}
			else
			{
				// Override Control
				if (Gamepad.GetRawButton(liftUpButton))
				{
					LiftInst.ManualOverride(true);
				}
				else if (Gamepad.GetRawButton(liftDownButton))
				{
					LiftInst.ManualOverride(false);
				}
				else
				{
					LiftInst.EndManualOverride();
				}
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
