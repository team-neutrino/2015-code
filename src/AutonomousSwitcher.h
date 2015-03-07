#include "WPILib.h"
#include "DigitalSelectorSwitch.h"
#include "Drive.h"
#include <thread>
#pragma once

class AutonomousSwitcher
{
public:
	AutonomousSwitcher(Drive* drive);
	void RunAuto();
	void ModeDriveForward();

private:
	DigitalSelectorSwitch Switch;
	std::thread DashboardThread;

	AutonomousDriver DriverInst;

	const double REFRESH_RATE = 5;

	void updateDashboardThread();
};
