/*
 * Lift.h
 *
 *  Created on: Jan 27, 2015
 *      Author: tianxinxu
 */
#include "WPILib.h"
#pragma once

class Lift
{
public:
	Lift ();
	void GoUp(int levels);
	void GoDown(int levels);
	int GetLevel();
	bool Lifting();

private:
	Victor LiftMotor1;
	Victor LiftMotor2;

};






