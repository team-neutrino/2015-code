#include "AutonomousSwitcher.h"
#include "Constants.h"
#include "DriverOutputs.h"
#include "string"

AutonomousSwitcher::AutonomousSwitcher(Drive* drive, Sucky* sucky, Lift* lift):
		Switch(Constants::GetConstant("AutonSwitchInput0Channel"),
				Constants::GetConstant("AutonSwitchInput1Channel"),
				Constants::GetConstant("AutonSwitchInput2Channel"),
				Constants::GetConstant("AutonSwitchInput3Channel")),
		DashboardThread(&AutonomousSwitcher::updateDashboardThread, this),
		DriverInst(drive)
{
	SuckyInst = sucky;
	LiftInst = lift;
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

			std::string description;
			switch (mode)
			{
				case 0:
					description = "Do Nothing!";
					break;
				case 1:
					description = "Drive Forward";
					break;
				case 2:
					description = "Drive Backward";
					break;
				case 3:
					description = "Three Tote Stacked";
					break;
				case 4:
					description = "Turn 90 and drive to zone";
					break;
				default:
					description =  "Auto mode not implemented";
					break;
			}

			DriverOutputs::UpdateSmartDashboardString("Autonomous Mode Description", description);

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
			DriverOutputs::ReportError("drive forward\n");
			ModeDriveForward();
			break;
		case 2:
			DriverOutputs::ReportError("3 stack totes\n");
			ModeThreeToteStack();
			break;
		case 3:
			DriverOutputs::ReportError("Turn 90 and drive forward\n");
			TurnWithTote();
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
	LiftInst->LevelChange(2);
	LiftInst->WaitForLift();
	Wait(.5);
	SuckyInst->Open(true);
	SuckyInst->SetLeft(.5);
	SuckyInst->SetRight(-.5);
	DriverInst.MoveDistance(3);
	SuckyInst->Open(false);
	DriverInst.MoveDistance(3);
	SuckyInst->Open(true);
	SuckyInst->SuckIn();
	Wait(1);
	SuckyInst->Open(false);
	LiftInst->LevelChange(-2);
	LiftInst->WaitForLift();
	LiftInst->LevelChange(2);
	SuckyInst->Open(true);
	SuckyInst->SetLeft(-.5);
	SuckyInst->SetRight(.5);
	DriverInst.MoveDistance(3, .75);
	SuckyInst->Open(false);
	DriverInst.MoveDistance(4);
	SuckyInst->Open(true);
	SuckyInst->SuckIn();
	Wait(1);
	SuckyInst->Open(false);
	SuckyInst->Stop();
	LiftInst->LevelChange(-2);
	LiftInst->WaitForLift();
	LiftInst->LevelChange(2);
	DriverInst.TurnDegrees(60);
	DriverInst.MoveDistance(6);
	LiftInst->Reset();
	LiftInst->WaitForLift();
	DriverInst.MoveDistance(-3);
}

void AutonomousSwitcher::TurnWithTote()
{
	DriverInst.TurnDegrees(60);
	DriverInst.MoveDistance(3);
}
