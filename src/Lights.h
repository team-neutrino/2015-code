#include "WPILib.h"
#include <Relay.h>

#pragma once

class Lights
{
public:
	Lights();
	void LightsPower(bool on);
private:
	void LightsPower1(bool on);
	void LightsPower2(bool on);
	void LightsPower3(bool on);
	Relay Relay1;
	Relay Relay2;
	Relay Relay3;
};
