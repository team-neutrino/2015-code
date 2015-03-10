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
	float degreechange = 20;
	float diagonalmove = 3;
	float straightmove = 5;
	float autonlongturn = 90;
	float autonlongmove = 1;
	//First Tote
	DriverInst.TurnDegrees(degreechange);
	SuckyInst->Stop();
	LiftInst->LevelChange(1);
	DriverInst.MoveDistance(diagonalmove);
	DriverInst.TurnDegrees(-degreechange);
	DriverInst.MoveDistance(straightmove);
	DriverInst.TurnDegrees(-degreechange);
	SuckyInst->SuckIn();
	DriverInst.MoveDistance(diagonalmove);
	//Second Tote
	SuckyInst->Open(true);
	Wait (1);
	SuckyInst->Open(false);
	LiftInst->LevelChange(-1);
	Wait (1);
	LiftInst->LevelChange(1);
	Wait (1);
	DriverInst.MoveDistance(-diagonalmove);
	DriverInst.TurnDegrees(degreechange);
	SuckyInst->Stop();
	DriverInst.MoveDistance(straightmove);
	DriverInst.TurnDegrees(-degreechange);
	SuckyInst->SuckIn();
	DriverInst.MoveDistance(diagonalmove);
	//Third Tote
	SuckyInst->Open(true);
	Wait (1);
	SuckyInst->Open(false);
	Wait (1);
	LiftInst->LevelChange(-1);
	Wait (1);
	DriverInst.MoveDistance(-diagonalmove);
	DriverInst.TurnDegrees(autonlongturn);
	DriverInst.MoveDistance(autonlongmove);
	SuckyInst->Stop();
	//Drop Stack
	SuckyInst->Open(false);
	DriverInst.MoveDistance(-1);
}
