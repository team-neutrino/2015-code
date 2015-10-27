#include "AutonomousSwitcher.h"
#include "Constants.h"
#include "DriverOutputs.h"
#include "string"

AutonomousSwitcher::AutonomousSwitcher(Drive* drive, Intake* sucky, Lift* lift, CanGrabberArm* spider):
		Switch(Constants::GetConstant("AutonSwitchInput0Channel"),
				Constants::GetConstant("AutonSwitchInput1Channel"),
				Constants::GetConstant("AutonSwitchInput2Channel"),
				Constants::GetConstant("AutonSwitchInput3Channel")),
		DashboardThread(&AutonomousSwitcher::updateDashboardThread, this),
		DriverInst(drive)
{
	SuckyInst = sucky;
	LiftInst = lift;
	CanGrabber = spider;
}

void AutonomousSwitcher::updateDashboardThread()
{
}

void AutonomousSwitcher::RunAuto()
{
	switch (MODE)
	{
		case 0:
			DriverOutputs::ReportError("Auto: none\n");
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
			DriverOutputs::ReportError("Auto: Grab the Cans in Timed Mode\n");
			TimeGrabCans();
			break;
		case 5:
			DriverOutputs::ReportError("Flip Can\n");
			TimeMoveForward();
			break;
		default:
			DriverOutputs::ReportError("Auto: No Such Autonomous Mode");
			break;
	}
}

void AutonomousSwitcher::ModeDriveForward()
{
	DriverInst.MoveDistance(4);
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
	SuckyInst->Open(true);
	SuckyInst->SetLeft(1);
	SuckyInst->SetRight(-1);
	// Moves to the second tote
	DriverStation::ReportError("3. Move 3 feet to the second tote\n");
	DriverInst.MoveDistance(2);
	// Opens for the second tote
	DriverStation::ReportError("4. Open for second tote\n");
	SuckyInst->Open(false);
	// Continues to move to the second tote
	DriverStation::ReportError("5. Move 3 feet to the second tote again\n");
	DriverInst.MoveDistance(1.75);
	// intakes the second tote
	DriverStation::ReportError("6. Intake the second tote\n");
	SuckyInst->Open(true);
	SuckyInst->SuckIn();
	Wait(1);
	SuckyInst->Open(false);
	// picks up the second tote
	DriverStation::ReportError("7. Pick up the second tote\n");
	LiftInst->LevelChange(-2);
	LiftInst->WaitForLift();
	LiftInst->LevelChange(2);
	// closes the intake and pushes away the container
	DriverStation::ReportError("8. Close intake and push away container\n");
	SuckyInst->Open(true);
	SuckyInst->SetLeft(-1);
	SuckyInst->SetRight(1);
	// slowly moves to the third tote and opens the intake
	DriverStation::ReportError("9. Move 3 feet toward the third tote at .75 * speed\n");
	DriverInst.MoveDistance(2.5);
	DriverStation::ReportError("10. Open the intake\n");
	SuckyInst->Open(false);
	DriverInst.MoveDistance(2.5);
	SuckyInst->SuckIn();
	SuckyInst->Open(true);
	DriverInst.MoveDistance(.5);
	// Intakes the third totes
	SuckyInst->Stop();
	// Turns and drives to the auton zone
	DriverInst.TurnDegrees(60);
	SuckyInst->Open(false);
	LiftInst->Reset();
	DriverInst.MoveDistance(2, 2);
	LiftInst->WaitForLift();
	DriverOutputs::ReportError("Driving back");
	DriverInst.MoveDistance(1.5, -2);
}

void AutonomousSwitcher::TurnWithTote()
{
	DriverInst.TurnDegrees(60);
	DriverInst.MoveDistance(3);
}

void AutonomousSwitcher::TimeGrabCans()
{
	DriverInst.MoveForTime(-.3);
	Wait (2);
	CanGrabber->CanGrabberToggle(true);
	Wait (5);
	DriverInst.MoveForTime(3);
	CanGrabber->CanGrabberToggle(false);
}

void AutonomousSwitcher::TimeMoveForward()
{
	DriverInst.MoveDistance(2, 1);
	DriverInst.MoveDistance(1.75, -1);
	LiftInst->Reset();
	LiftInst->WaitForLift();
	SuckyInst->Open(true);
	SuckyInst->SuckIn();
	Wait(2);
	SuckyInst->Open(false);
	DriverInst.MoveDistance(2.75, 1);
	Wait(1);
	Wait(1);
	LiftInst->LevelChange(3);
}
