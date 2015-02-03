#include "DigitalSelectorSwitch.h"

DigitalSelectorSwitch::DigitalSelectorSwitch(int input0Channel,
		int input1Channel, int input2Channel, int input3Channel):
		Input0(input0Channel),
		Input1(input1Channel),
		Input2(input2Channel),
		Input3(input3Channel)
{

}

int DigitalSelectorSwitch::Read()
{
	return !Input0.Get() + 2 * !Input1.Get() + 4 * !Input2.Get()
			+ 8 * !Input3.Get();
}

