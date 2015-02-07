#include "WPILib.h"
#include "Lift.h"
#include "Constants.h"
#include "AutonomousSwitcher.h"
#include "Drive.h"

class Robot: public SampleRobot
{

public:
	AutonomousSwitcher AutoSwitch;
	Joystick JoyRight;
	Joystick JoyLeft;
	Drive DriveInst;
	Lift LiftInst;

	/**
	 * Constructor
	 */
	Robot():
		AutoSwitch(),
		JoyRight(Constants::GetConstant("JoyRightPort")),
		JoyLeft(Constants::GetConstant("JoyLeftPort")),
		DriveInst(),
		LiftInst()
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
			//Drive Loop
			driveMultiplier =(JoyLeft.GetRawButton(1) || JoyRight.GetRawButton(1)) ?
								driveFastMultiplier : driveSlowMultiplier;
			DriveInst.SetLeft(-JoyLeft.GetY() * fabs(JoyLeft.GetY()) * driveMultiplier);
			DriveInst.SetRight(JoyRight.GetY() * fabs(JoyRight.GetY()) * driveMultiplier);


			// Lift Test Code
//			if(JoyLeft.GetRawButton(1))
//			{
//				LiftInst.LevelChange(2);
//			}
//
//			if(JoyLeft.GetRawButton(2))
//			{
//				LiftInst.Reset();
//			}
//
//			if(JoyLeft.GetRawButton(3))
//			{
//				LiftInst.LevelChange(-2);
//			}

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
