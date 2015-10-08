#include "WPILib.h"
#include "DigitalSelectorSwitch.h"
#include "Drive.h"
#include "AutonomousDriver.h"
#include "Sucky.h"
#include "Lift.h"
#include <thread>
#include "CanGrabberArm.h"
#pragma once

class AutonomousSwitcher
{
public:
	AutonomousSwitcher(Drive* drive, Sucky* sucky, Lift* lift, CanGrabberArm* spider);
	void RunAuto();
	void ModeDriveForward();
	void ModeDriveBackward();
	void ModeThreeToteStack();
	void TurnWithTote();
	void ModeCanGrab();

	void TimeThreeTote();
	void TimeMoveForward();
	void TimeGrabCans();

private:
	DigitalSelectorSwitch Switch;
	std::thread DashboardThread;

	CanGrabberArm* CanGrabber;

	AutonomousDriver DriverInst;

	Sucky* SuckyInst;

	Lift* LiftInst;

	const double REFRESH_RATE = 5;

	void updateDashboardThread();
};
