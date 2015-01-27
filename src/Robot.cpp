#include "WPILib.h"
#include "Constants.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{

public:
	/**
	 * Constructor
	 */
	Robot()
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

	}

	/**
	 * Operator Control mode
	 */
	void OperatorControl()
	{

	}

	/**
	 * Test mode
	 */
	void Test()
	{

	}
};

START_ROBOT_CLASS(Robot);
