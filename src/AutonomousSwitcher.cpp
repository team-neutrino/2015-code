#include "AutonomousSwitcher.h"
#include "Constants.h"

AutonomousSwitcher::AutonomousSwitcher():
		Switch(Constants::GetConstant("AutonSwitchInput0Channel"),
				Constants::GetConstant("AutonSwitchInput1Channel"),
				Constants::GetConstant("AutonSwitchInput2Channel"),
				Constants::GetConstant("AutonSwitchInput3Channel")),
		DashboardThread(&AutonomousSwitcher::updateDashboardThread, this)
{

}

void AutonomousSwitcher::updateDashboardThread()
{
	while (true)
	{
		int mode = Switch.Read();
		SmartDashboard::PutNumber("Autonomous Mode", mode);

		switch (mode)
		{
			case 0:
				SmartDashboard::PutString("Autonomous Mode Description", "Do Nothing!");
				break;
			default:
				SmartDashboard::PutString("Autonomous Mode Description", "Auto mode not implemented");
				break;
		}
		Wait(1);
	}
}

void AutonomousSwitcher::RunAuto()
{
	switch (Switch.Read())
	{
		case 0:
			break;
		default:
			DriverStation::ReportError("No Such Autonomous Mode");
			break;
	}
}
