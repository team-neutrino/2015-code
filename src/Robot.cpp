#include "WPILib.h"
#include "Lift.h"
#include "Constants.h"
#include "AutonomousSwitcher.h"
#include "Drive.h"
#include "Sucky.h"
#include "DriverOutputs.h"
#include "CurrentMonitor.h"
#include "AutonomousDriver.h"
#include "Lights.h"
#include "DeadSpider.h"
#include "StackJail.h"

class Robot: public SampleRobot
{

public:
	Constants ConstInst;
	Compressor Comp;
	Joystick JoyRight;
	Joystick JoyLeft;
	Joystick Gamepad;
	Drive DriveInst;
	Lift LiftInst;
	Sucky SuckyInst;
	AutonomousSwitcher AutoSwitch;
	CurrentMonitor CurrentMonitorInst;
	Lights Lightshow;
	DeadSpider CanWhip;
	StackJail Chopsticks;

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
		AutoSwitch(&DriveInst, &SuckyInst, &LiftInst),
		CurrentMonitorInst(),
		Lightshow(),
		CanWhip()
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
		// Drive multiplier variables
		float driveSlowMultiplier = Constants::GetConstant("DriveSlowMultiplier");
		float driveFastMultiplier = Constants::GetConstant("DriveFastMultiplier");
		float driveMultiplier = driveFastMultiplier;

		// Speed boost variable
		int speedBoostButton = Constants::GetConstant("SpeedBoostButton");

		// Intake variables
		int suckyXAxis = Constants::GetConstant("SuckyXAxis");
		int suckyYAxis = Constants::GetConstant("SuckyYAxis");

		// Lift variables
		int liftUpButton = Constants::GetConstant("LiftUpButton");
		int liftDownButton = Constants::GetConstant("LiftDownButton");
		int liftResetButton = Constants::GetConstant("LiftResetButton");
		int liftOverrideUp = Constants::GetConstant("LiftOverrideUp");
		int liftOverrideDown = Constants::GetConstant("LiftOverrideDown");
//		int liftAutoStackButton = Constants::GetConstant("LiftAutoStackButton");

		//TODO Implement Autostacking
		bool autoStacking = false;

		while(IsOperatorControl() && IsEnabled())
		{
			// Drive Controls
			driveMultiplier =(JoyLeft.GetRawButton(speedBoostButton) || JoyRight.GetRawButton(speedBoostButton)) ?
								driveFastMultiplier : driveSlowMultiplier;
			DriveInst.SetLeft(-JoyLeft.GetY() * fabs(JoyLeft.GetY()) * driveMultiplier);
			DriveInst.SetRight(-JoyRight.GetY() * fabs(JoyRight.GetY()) * driveMultiplier);

			// Spins the intake wheels at speeds based on the game controller sticks
			SuckyInst.SetLeft(Gamepad.GetRawAxis(suckyYAxis) + Gamepad.GetRawAxis(suckyXAxis));
			SuckyInst.SetRight(Gamepad.GetRawAxis(suckyYAxis) - Gamepad.GetRawAxis(suckyXAxis));

			// Opens or closes the intake
			SuckyInst.Open(Gamepad.GetRawButton(Constants::GetConstant("SuckyOpenButton")));

			// Lift Controls
			if (!Gamepad.GetRawButton(liftOverrideUp) && !Gamepad.GetRawButton(liftOverrideDown))
			{
				// Ends manual override if it was enabled
				LiftInst.EndManualOverride();

				// Normal Control
				if (!LiftInst.Lifting())
				{
					// TODO Auto stack ability
					if (autoStacking)
					{
						LiftInst.LevelChange(1);
						autoStacking = false;
					}

					// Regular automated lift control
					else
					{
						if (JoyLeft.GetRawButton(liftResetButton) ||
								JoyRight.GetRawButton(liftResetButton))
						{
							LiftInst.Reset();
						}
						// sends lift up a level
						else if (Gamepad.GetRawButton(liftUpButton))
						{
							LiftInst.LevelChange(1);
						}
						// sends lift down a level
						else if (Gamepad.GetRawButton(liftDownButton))
						{
							LiftInst.LevelChange(-1);
						}
						// TODO Implement Auto stacking
//						else if (Gamepad.GetRawButton(liftAutoStackButton))
//						{
//							LiftInst.LevelChange(-1);
//							autoStacking = true;
//						}
					}
				}
			}
			else
			{
				// Override Control
				autoStacking = false;

				// Moves lift up while button is pressed
				if (Gamepad.GetRawButton(liftOverrideUp))
				{
					LiftInst.ManualOverride(true);
				}

				// Moves lift down while button is pressed
				else if (Gamepad.GetRawButton(liftOverrideDown))
				{
					LiftInst.ManualOverride(false);
				}

				// Ends manual override
				else
				{
					LiftInst.ManualOverrideStopped();
				}
			}
			//DeadSpider Override
			CanWhip.SpiderToggle(JoyLeft.GetRawButton(Constants::GetConstant("DeadSpiderWhip")) ||
					JoyRight.GetRawButton(Constants::GetConstant("DeadSpiderWhip")));

			//Chopsticks Override
			Chopsticks.GateToggle(Gamepad.GetRawButton(Constants::GetConstant("StackJailOverrideOpen")));

			// Current Warning - rumbles when breaker is about to blow
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

			// SmartDashboard Test
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
