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
					description = "Turn 90 and drive to zone";
					break;
				case 4:
					description = "Grab the Cans";
					break;
				case 5:
					description = "Grab Cans in Time Mode";
					break;
				case 6:
					description = "Drive Forward in Time Mode";
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
			DriverOutputs::ReportError("Auto: drive forward\n");
			ModeDriveForward();
			break;
		case 2:
			DriverOutputs::ReportError("Auto: 3 stack totes\n");
			ModeThreeToteStack();
			break;
		case 3:
			DriverOutputs::ReportError("Auto: Turn 90 and drive forward\n");
			TurnWithTote();
			break;
		case 4:
			DriverOutputs::ReportError("Auto: Grab Those Cans!\n I need Cans!\n DEAD SPEIDER AWAY!!!!\n");
			ModeCanGrab();
			break;
		case 5:
			DriverOutputs::ReportError("Auto: Grab the Cans in Timed Mode\n");
			TimeGrabCans();
			break;
		case 6:
			DriverOutputs::ReportError("Auto: Move Forward in Time Mode\n");
			TimeMoveForward();
			break;
		default:
			DriverOutputs::ReportError("Auto: No Such Autonomous Mode");
			break;
	}
}

void AutonomousSwitcher::ModeDriveForward()
{
	DriverInst.MoveDistance(1);
}

// stacks three totes - make sure the lift is at the first flag
void AutonomousSwitcher::ModeThreeToteStack()
{
	// Lift goes up two levels
	DriverStation::ReportError("1. Lift up two levels\n");
	LiftInst->LevelChange(2);
	LiftInst->WaitForLift();
	Wait(.5);
	// Pushes the recycling container out of the way
	DriverStation::ReportError("2. Push the recycling container\n");
	SuckyInst->Open(false);
	SuckyInst->SetLeft(.75);
	SuckyInst->SetRight(-.75);
	// Moves to the second tote
	DriverStation::ReportError("3. Move 3 feet to the second tote\n");
	DriverInst.MoveDistance(3);
	// Opens for the second tote
	DriverStation::ReportError("4. Open for second tote\n");
	SuckyInst->Open(true);
	// Continues to move to the second tote
	DriverStation::ReportError("5. Move 3 feet to the second tote again\n");
	DriverInst.MoveDistance(3);
	// intakes the second tote
	DriverStation::ReportError("6. Intake the second tote\n");
	SuckyInst->Open(false);
	SuckyInst->SuckIn();
	Wait(1);
	SuckyInst->Open(true);
	// picks up the second tote
	DriverStation::ReportError("7. Pick up the second tote\n");
	LiftInst->LevelChange(-2);
	LiftInst->WaitForLift();
	LiftInst->LevelChange(2);
	// closes the intake and pushes away the container
	DriverStation::ReportError("8. Close intake and push away container\n");
	SuckyInst->Open(false);
	SuckyInst->SetLeft(-.75);
	SuckyInst->SetRight(.75);
	// slowly moves to the third tote and opens the intake
	DriverStation::ReportError("9. Move 3 feet toward the third tote at .75 * speed\n");
	DriverInst.MoveDistance(3, .75);
	DriverStation::ReportError("10. Open the intake\n");
	SuckyInst->Open(true);
	DriverInst.MoveDistance(4);
	// Intakes the third tote
	SuckyInst->Open(false);
	SuckyInst->SuckIn();
	Wait(1);
	SuckyInst->Open(true);
	SuckyInst->Stop();
	// Picks up the third tote
	LiftInst->LevelChange(-2);
	LiftInst->WaitForLift();
	LiftInst->LevelChange(2);
	// Turns and drives to the auton zone
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

void AutonomousSwitcher::ModeCanGrab()
{
	DriverInst.MoveDistance(-.5);
	CanGrabber.SpiderToggle(true);
	DriverInst.MoveDistance(-1);
	DriverInst.MoveDistance(5);
}

void AutonomousSwitcher::TimeGrabCans()
{
	DriverInst.MoveForTime(-.5);
	CanGrabber.SpiderToggle(true);
	DriverInst.MoveForTime(2);
}

void AutonomousSwitcher::TimeMoveForward()
{
	DriverInst.MoveForTime(2);
}
