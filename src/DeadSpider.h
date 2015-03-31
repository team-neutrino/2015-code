#include "WPILib.h"
#include "Constants.h"
#pragma once

class DeadSpider {
public:
	DeadSpider();

	void SpiderToggle(bool on);
private:
	Solenoid whipUp;
	Solenoid whipDown;
};

