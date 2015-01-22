/*
 * Switch.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: Neutrino
 */

#include "DigitalSelectorSwitch.h"

DigitalSelectorSwitch::DigitalSelectorSwitch() :
		Input0(0), Input1(1), Input2(2), Input3(3)
{

}

int DigitalSelectorSwitch::Read()
{
	return !Input0.Get() + 2 * !Input1.Get() + 4 * !Input2.Get() + 8 * !Input3.Get();
}

