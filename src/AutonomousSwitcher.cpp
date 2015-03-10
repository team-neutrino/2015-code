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
	//First Tote
	DriverInst.TurnDegrees(35);
	LiftInst->LevelChange(1);
	//Move out 3
	DriverInst.MoveDistance(3);
	//Turn to long move
	DriverInst.TurnDegrees(-23);
	//Long move
	DriverInst.MoveDistance(2);
	//Turn to diagonal move
	DriverInst.TurnDegrees(-20);
	SuckyInst->SuckIn();
	//Diagonal move
	DriverInst.MoveDistance(3);
	//Second Tote
	SuckyInst->Open(true);
	Wait (1);
	SuckyInst->Open(false);
	LiftInst->LevelChange(-1);
	LiftInst->WaitForLift();
	LiftInst->LevelChange(1);
	Wait (1);
	//Back up for long move
	DriverInst.MoveDistance(-3);
	//Turn to face long move
	DriverInst.TurnDegrees(20);
	SuckyInst->Stop();
	//Long move to tote three
	DriverInst.MoveDistance(6);
	//Turn to diagonal for tote 3
	DriverInst.TurnDegrees(-20);
	SuckyInst->SuckIn();
	//Move to pick up tote three
	DriverInst.MoveDistance(3);
	//Third Tote pickup
	SuckyInst->Open(true);
	Wait (1);
	SuckyInst->Open(false);
	Wait (1);
	LiftInst->LevelChange(-1);
	LiftInst->WaitForLift();
	LiftInst->LevelChange(1);
	//Back up from tote three
	DriverInst.MoveDistance(-3);
	//Turn to go toward auto zone
	DriverInst.TurnDegrees(90);
	//Move to auto zone
	DriverInst.MoveDistance(1);
	SuckyInst->Stop();
	//Drop Stack
	SuckyInst->Open(false);
	LiftInst->LevelChange(-1);
	LiftInst->WaitForLift();
	//Back up from stack
	DriverInst.MoveDistance(-1);
}
