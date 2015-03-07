#include "WPILib.h"
#include "Lift.h"
#include "Constants.h"
#include "AutonomousSwitcher.h"
#include "Drive.h"
#include "Sucky.h"
#include "DriverOutputs.h"
#include "CurrentMonitor.h"
#include "AutonomousDriver.h"

class Robot: public SampleRobot
{

public:
	Constants ConstInst;
	AutonomousSwitcher AutoSwitch;
	Compressor Comp;
	Joystick JoyRight;
	Joystick JoyLeft;
	Joystick Gamepad;
	Drive DriveInst;
	Lift LiftInst;
	Sucky SuckyInst;
	CurrentMonitor CurrentMonitorInst;

	/**
	 * Constructor
	 */
	Robot():
		ConstInst(),
		Comp(),
		JoyRight(Constants::GetConstant("JoyRightPort")),
		JoyLeft(Constants::GetConstant("JoyLeftPort")),
		Gamepad(Constants::GetConstant("GamepadPort")),
		DriveInst(),
		LiftInst(),
		SuckyInst(),
		AutoSwitch(&DriveInst),
		CurrentMonitorInst()
	{

	}

	/**
	 * Robot Initialization
	 */
	void RobotInit()
	{

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
		int suckyXAxis = Constants::GetConstant("SuckyXAxis");
		int suckyYAxis = Constants::GetConstant("SuckyYAxis");

		int liftUpButton = Constants::GetConstant("LiftUpButton");
		int liftDownButton = Constants::GetConstant("LiftDownButton");
		int liftResetButton = Constants::GetConstant("LiftResetButton");
		int liftOverrideButton = Constants::GetConstant("LiftOverrideButton");
		int liftAutoStackButton = Constants::GetConstant("LiftAutoStackButton");

		int joyLiftResetButton = Constants::GetConstant("JoyLiftResetButton");

		bool autoStacking = false;

		while(IsOperatorControl() && IsEnabled())
		{
			// Drive Controls
			driveMultiplier =(JoyLeft.GetRawButton(speedBoostButton) || JoyRight.GetRawButton(speedBoostButton)) ?
								driveFastMultiplier : driveSlowMultiplier;
			DriveInst.SetLeft(JoyLeft.GetY() * fabs(JoyLeft.GetY()) * driveMultiplier);
			DriveInst.SetRight(JoyRight.GetY() * fabs(JoyRight.GetY()) * driveMultiplier);

			// Sucky Controls
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
				SuckyInst.SetLeft(Gamepad.GetRawAxis(suckyYAxis) + Gamepad.GetRawAxis(suckyXAxis));
				SuckyInst.SetRight(Gamepad.GetRawAxis(suckyYAxis) - Gamepad.GetRawAxis(suckyXAxis));
			}

			SuckyInst.Open(Gamepad.GetRawButton(Constants::GetConstant("SuckyOpenButton")));

			// Lift Controls
			if (!Gamepad.GetRawButton(liftOverrideButton))
			{
				LiftInst.EndManualOverride();
				// Normal Control
				if (!LiftInst.Lifting())
				{
					if (autoStacking)
					{
						LiftInst.LevelChange(1);
						autoStacking = false;
					}
					else
					{
						if (Gamepad.GetRawButton(liftResetButton) ||
								JoyLeft.GetRawButton(joyLiftResetButton) ||
								JoyRight.GetRawButton(joyLiftResetButton))
						{
							LiftInst.Reset();
						}
						else if (Gamepad.GetRawButton(liftUpButton))
						{
							LiftInst.LevelChange(1);
						}
						else if (Gamepad.GetRawButton(liftDownButton))
						{
							LiftInst.LevelChange(-1);
						}
						else if (Gamepad.GetRawButton(liftAutoStackButton))
						{
							LiftInst.LevelChange(-1);
							autoStacking = true;
						}
					}
				}
			}
			else
			{
				// Override Control
				autoStacking = false;

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
					LiftInst.ManualOverrideStopped();
				}
			}

			// Current Warning
			if(CurrentMonitorInst.Warning() || JoyRight.GetRawButton(11))
			{
				Gamepad.SetRumble(Joystick::kLeftRumble, 1);
				Gamepad.SetRumble(Joystick::kRightRumble, 1);
			}
			else
			{
				Gamepad.SetRumble(Joystick::kLeftRumble, 0);
				Gamepad.SetRumble(Joystick::kRightRumble, 0);
			}

			DriverOutputs::UpdateSmartDashboardBoolean("Test", JoyRight.GetRawButton(11));

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
