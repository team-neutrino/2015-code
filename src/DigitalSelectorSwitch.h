/*
 * Switch.h
 *
 *  Created on: Jan 16, 2015
 *      Author: Neutrino
 */
#include "WPILib.h"
#pragma once

class DigitalSelectorSwitch
{
public:
	DigitalSelectorSwitch();
	DigitalInput Input0;
	DigitalInput Input1;
	DigitalInput Input2;
	DigitalInput Input3;

	int Read();
};
