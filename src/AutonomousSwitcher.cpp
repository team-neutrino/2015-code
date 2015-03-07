#include "AutonomousSwitcher.h"
#include "Constants.h"
#include "DriverOutputs.h"

AutonomousSwitcher::AutonomousSwitcher(Drive* drive):
		Switch(Constants::GetConstant("AutonSwitchInput0Channel"),
				Constants::GetConstant("AutonSwitchInput1Channel"),
				Constants::GetConstant("AutonSwitchInput2Channel"),
				Constants::GetConstant("AutonSwitchInput3Channel")),
		DashboardThread(&AutonomousSwitcher::updateDashboardThread, this),
		DriverInst(drive),
		Intake(),
		Lifter()
{

}

void AutonomousSwitcher::updateDashboardThread()
{
	int mode;
	int modePrev = 0;

	double lastRefresh = GetTime() + REFRESH_RATE;

	while (true)
	{
		mode = Switch.Read();
		if(mode != modePrev || ((GetTime() - lastRefresh) >= REFRESH_RATE))
		{
			lastRefresh = GetTime();

			DriverOutputs::UpdateSmartDashboardNumber("Autonomous Mode", mode);

			switch (mode)
			{
				case 0:
					DriverOutputs::UpdateSmartDashboardString("Autonomous Mode Description", "Do Nothing!");
					break;
				default:
					DriverOutputs::UpdateSmartDashboardString("Autonomous Mode Description", "Auto mode not implemented");
					break;
			}

			modePrev = mode;
		}

		Wait(1);
	}
}

void AutonomousSwitcher::RunAuto()
{
	switch (Switch.Read())
	{
		case 0:
			break;
		case 1:
			ModeDriveForward();
			break;
		case 2:
			ModeThreeToteStack();
			break;
		default:
			DriverOutputs::ReportError("No Such Autonomous Mode");
			break;
	}
}

void AutonomousSwitcher::ModeDriveForward()
{
	DriverInst.MoveDistance(3);
}

void AutonomousSwitcher::ModeThreeToteStack()
{
	float degreechange = 15;
	float diagonalmove = 3;
	float straightmove = 3;
	//First Tote
	Intake.Open(false);
	Intake.SuckIn();
	Lifter.LevelChange(-1);
	DriverInst.TurnDegrees(degreechange);
	Intake.Stop();
	Lifter.LevelChange(1);
	DriverInst.MoveDistance(diagonalmove);
	DriverInst.TurnDegrees(-degreechange);
	DriverInst.MoveDistance(straightmove);
	DriverInst.TurnDegrees(degreechange);
	Intake.Open(true);
	Intake.SuckIn();
	DriverInst.MoveDistance(diagonalmove);
	//Second Tote
	Intake.Open(false);
	Lifter.LevelChange(-1);
	DriverInst.MoveDistance(-diagonalmove);
	DriverInst.TurnDegrees(-degreechange);
	Intake.Stop();
	Lifter.LevelChange(1);
	DriverInst.MoveDistance(straightmove);
	DriverInst.TurnDegrees(degreechange);
	Intake.Open(true);
	Intake.SuckIn();
	DriverInst.MoveDistance(diagonalmove);
	//Third Tote
	Intake.Open(false);
	Lifter.LevelChange(-1);
	DriverInst.MoveDistance(-diagonalmove);
	DriverInst.TurnDegrees(-90);
	DriverInst.MoveDistance(9);
	Intake.Stop();
	//Drop Stack
	Intake.Open(true);
	DriverInst.MoveDistance(-1);
}
