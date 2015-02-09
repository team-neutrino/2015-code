#include "WPILib.h"
#include "DigitalSelectorSwitch.h"
#include <thread>
#pragma once

class AutonomousSwitcher
{
public:
	AutonomousSwitcher();
	void RunAuto();


private:
	DigitalSelectorSwitch Switch;
	std::thread DashboardThread;

	const double REFRESH_RATE = 5;

	void updateDashboardThread();
};
