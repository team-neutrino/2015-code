#include "CurrentMonitor.h"
#include "DriverOutputs.h"
#include "Constants.h"

CurrentMonitor::CurrentMonitor():
	Pdp(),
	Thread(&CurrentMonitor::currentThread, this)
{
	PdpAttached = Constants::GetConstant("PdpAttached") == 1;
}

bool CurrentMonitor::Warning()
{
	return PdpAttached && WARNING_CURRENT <= Pdp.GetTotalCurrent();
}

void CurrentMonitor::currentThread()
{
	int driveLeft1Channel = Constants::GetConstant("DriveLeft1PowerChannel");
	int driveLeft2Channel = Constants::GetConstant("DriveLeft2PowerChannel");
	int driveRight1Channel = Constants::GetConstant("DriveRight1PowerChannel");
	int driveRight2Channel = Constants::GetConstant("DriveRight2PowerChannel");

	int lift1Channel = Constants::GetConstant("LiftMotor1PowerChannel");
	int lift2Channel = Constants::GetConstant("LiftMotor2PowerChannel");

	int suckyLeftChannel = Constants::GetConstant("IntakeMotorLeftPowerChannel");
	int suckyRightChannel = Constants::GetConstant("IntakeMotorRightPowerChannel");

	while (PdpAttached)
	{
		// Total Current
		DriverOutputs::UpdateSmartDashboardBoolean("Warning", WARNING_CURRENT <= Pdp.GetTotalCurrent());
		DriverOutputs::UpdateSmartDashboardNumber("Total Current", Pdp.GetTotalCurrent());

		// Drive
		double driveLeft1Current = Pdp.GetCurrent(driveLeft1Channel);
		double driveLeft2Current = Pdp.GetCurrent(driveLeft2Channel);
		double driveRight1Current = Pdp.GetCurrent(driveRight1Channel);
		double driveRight2Current = Pdp.GetCurrent(driveRight2Channel);

		DriverOutputs::UpdateSmartDashboardNumber("Total Drive Current",
				driveLeft1Current + driveLeft2Current
						+ driveRight1Current + driveRight2Current);
		DriverOutputs::UpdateSmartDashboardNumber("Drive Left 1 Current", driveLeft1Current);
		DriverOutputs::UpdateSmartDashboardNumber("Drive Left 2 Current", driveLeft2Current);
		DriverOutputs::UpdateSmartDashboardNumber("Drive Right 1 Current", driveRight1Current);
		DriverOutputs::UpdateSmartDashboardNumber("Drive Right 2 Current", driveRight2Current);

		// Lift
		double lift1Current = Pdp.GetCurrent(lift1Channel);
		double lift2Current = Pdp.GetCurrent(lift2Channel);
		DriverOutputs::UpdateSmartDashboardNumber("Total Lift Current", lift1Current + lift2Current);
		DriverOutputs::UpdateSmartDashboardNumber("Lift 1 Current", lift1Current);
		DriverOutputs::UpdateSmartDashboardNumber("Lift 2 Current", lift2Current);

		// Sucky
		double suckyLeftCurrent = Pdp.GetCurrent(suckyLeftChannel);
		double suckyRightCurrent = Pdp.GetCurrent(suckyRightChannel);
		DriverOutputs::UpdateSmartDashboardNumber("Total Sucky Current", suckyLeftCurrent + suckyRightCurrent);
		DriverOutputs::UpdateSmartDashboardNumber("Sucky Left Current", suckyLeftCurrent);
		DriverOutputs::UpdateSmartDashboardNumber("Sucky Right Current", suckyRightCurrent);

		Wait(.1);
	}

}
