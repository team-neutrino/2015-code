#include "WPILib.h"
#pragma once

class DigitalSelectorSwitch
{
public:
	DigitalSelectorSwitch(int input0Channel, int input1Channel,
			int input2Channel, int input3Channel);

	/**
	 * Returns the state of all 4 inputs as a 4-bit binary digit.
	 */
	int Read();

private:
	DigitalInput Input0;
	DigitalInput Input1;
	DigitalInput Input2;
	DigitalInput Input3;
};
