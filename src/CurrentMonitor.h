#include "WPILib.h"
#include <thread>

#pragma once

class CurrentMonitor
{
public:
	CurrentMonitor();
	bool Warning();

private:
	const double WARNING_CURRENT = 120;

	bool PdpAttached;

	PowerDistributionPanel Pdp;
	std::thread Thread;

	void currentThread();
};
