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
					description = "Three Tote Stacked";
					break;
				case 3:
					description = "Drive Backward";
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
			ModeDriveForward();
			break;
		case 2:
			ModeThreeToteStack();
			break;
		case 3:
			ModeDriveBackward();
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


	//First Tote
	LiftInst->LevelChange(1);
	DriverInst.TurnDegrees(35);
	//diagonal move
	DriverInst.MoveDistance(2);
	DriverInst.TurnDegrees(-20);
	//Begin long turn
	DriverInst.MoveDistance(1.7);
	SuckyInst->SuckIn();
	DriverInst.TurnDegrees(-45);
	//Begin hard turn
	DriverInst.MoveDistance(1.7);
	DriverInst.TurnDegrees(30);
	//Begin tote-grabbing move
	DriverInst.MoveDistance(1);
	Wait (1);
	//Second Tote
	SuckyInst->Open(true);
	Wait (1);
	SuckyInst->Open(false);
	Wait (1);
	LiftInst->LevelChange(-1);
	LiftInst->WaitUntilLiftComplete();
	LiftInst->LevelChange(1);
	Wait (1);
	//Back Up with tote
	DriverInst.MoveDistance(-1);
	DriverInst.TurnDegrees(-45);
	//Back up to long move position
	DriverInst.MoveDistance(-2);
	SuckyInst->Stop();
	//Long Move to Tote 3
	DriverInst.MoveDistance(3.5);
	DriverInst.TurnDegrees(-20);
	SuckyInst->SuckIn();
	//
	DriverInst.MoveDistance(2);
	DriverInst.TurnDegrees(45);
	DriverInst.MoveDistance(1);
	Wait (1);
	//Third Tote
	SuckyInst->Open(true);
	Wait (1);
	SuckyInst->Open(false);
	Wait (1);
	LiftInst->LevelChange(-1);
	LiftInst->WaitUntilLiftComplete();
	LiftInst->LevelChange(1);
	Wait (1);
	//Back Up
	DriverInst.MoveDistance(-1);
	DriverInst.TurnDegrees(-45);
	DriverInst.MoveDistance(-2);
	SuckyInst->Stop();
	//Drop Stack
	SuckyInst->Open(false);
	Wait (1);
	LiftInst-> LevelChange(-1);
	DriverInst.MoveDistance(-1);
}

void AutonomousSwitcher::ModeDriveBackward()
{
	DriverInst.MoveDistance(-3);
}
