#include "AutonomousSwitcher.h"
#include "Constants.h"
#include "DriverOutputs.h"

AutonomousSwitcher::AutonomousSwitcher(Drive* drive):
		Switch(Constants::GetConstant("AutonSwitchInput0Channel"),
				Constants::GetConstant("AutonSwitchInput1Channel"),
				Constants::GetConstant("AutonSwitchInput2Channel"),
				Constants::GetConstant("AutonSwitchInput3Channel")),
		DashboardThread(&AutonomousSwitcher::updateDashboardThread, this),
		DriverInst(drive)
{

}

void AutonomousSwitcher::updateDashboardThread()
{
	int mode;
	int modePrev = 0;

	double lastRefresh = GetTime() + REFRESH_RATE;

	while (true)
	{
		mode = Switch.Read();
		if(mode != modePrev || ((GetTime() - lastRefresh) >= REFRESH_RATE))
		{
			lastRefresh = GetTime();

			DriverOutputs::UpdateSmartDashboardNumber("Autonomous Mode", mode);

			switch (mode)
			{
				case 0:
					DriverOutputs::UpdateSmartDashboardString("Autonomous Mode Description", "Do Nothing!");
					break;
				default:
					DriverOutputs::UpdateSmartDashboardString("Autonomous Mode Description", "Auto mode not implemented");
					break;
			}

			modePrev = mode;
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
		case 1:
			ModeDriveForward();
			break;
		default:
			DriverOutputs::ReportError("No Such Autonomous Mode");
			break;
	}
}

void AutonomousSwitcher::ModeDriveForward()
{

}
