#include "WPILib.h"
#include "DigitalSelectorSwitch.h"
#include <thread>
#pragma once

class AutonomousSwitcher
{
public:
	AutonomousSwitcher();
	void RunAuto();
	void updateDashboard();

private:
	DigitalSelectorSwitch Switch;
	std::thread DashboardThread;
};
