#include "Lights.h"
#include "Constants.h"

Lights::Lights():
	Relay1(Constants::GetConstant("LightsChannel1")),
	Relay2(Constants::GetConstant("LightsChannel2")),
	Relay3(Constants::GetConstant("LightsChannel3"))
{

}
/*
void Lights::LightsPower1(bool on)
{
	if(on)
	{
		Relay1.Set(Relay::kOn);
	}
	else
	{
		Relay1.Set(Relay::kOff);
	}
}

void Lights::LightsPower2(bool on)
{
	if(on)
	{
		Relay2.Set(Relay::kOn);
	}
	else
	{
		Relay2.Set(Relay::kOff);
	}
}

void Lights::LightsPower3(bool on)
{
	if(on)
	{
		Relay3.Set(Relay::kOn);
	}
	else
	{
		Relay3.Set(Relay::kOff);
	}
}
*/

void Lights::LightsPower1(bool on)
{
	Relay1.Set(on ? Relay::kOn : Relay::kOff);
}

void Lights::LightsPower2(bool on)
{
//
	Relay2.Set(on ? Relay::kOn : Relay::kOff);
}
//
//
void Lights::LightsPower3(bool on)
//
{
	Relay3.Set(on ? Relay::kOn : Relay::kOff);
}
//
void Lights::LightsPower(bool on)
{
	//
	LightsPower1(on);
	LightsPower2(on);
	//
	LightsPower3(on);
}
//
