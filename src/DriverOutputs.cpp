#include "WPILib.h"
#include "DriverOutputs.h"

const double DriverOutputs::COMP_TIME = 1426842000;

bool DriverOutputs::UpdateErrors = false;
std::queue<DriverOutputs::Error> DriverOutputs::ErrorQueue;
std::mutex DriverOutputs::MtxError;

bool DriverOutputs::UpdateDashboard = false;
std::queue<DriverOutputs::DashboardBoolean> DriverOutputs::DashboardBooleanQueue;
std::queue<DriverOutputs::DashboardNumber> DriverOutputs::DashboardNumberQueue;
std::queue<DriverOutputs::DashboardString> DriverOutputs::DashboardStringQueue;
std::mutex DriverOutputs::MtxDashboard;

std::thread DriverOutputs::Thread(DriverOutputs::run);

void DriverOutputs::ReportError(std::string error)
{
	MtxError.lock();
	ErrorQueue.push({GetTime(), error});
	UpdateErrors = true;
	MtxError.unlock();
}

void DriverOutputs::UpdateSmartDashboardBoolean(std::string key, bool boolean)
{
	MtxDashboard.lock();
	DashboardBooleanQueue.push({key, boolean});
	UpdateDashboard = true;
	MtxDashboard.unlock();
}

void DriverOutputs::UpdateSmartDashboardNumber(std::string key, double number)
{
	MtxDashboard.lock();
	DashboardNumberQueue.push({key, number});
	UpdateDashboard = true;
	MtxDashboard.unlock();
}

void DriverOutputs::UpdateSmartDashboardString(std::string key, std::string string)
{
	MtxDashboard.lock();
	DashboardStringQueue.push({key, string});
	UpdateDashboard = true;
	MtxDashboard.unlock();
}

void DriverOutputs::sendErrors()
{
	while(!ErrorQueue.empty())
	{
		Error e = ErrorQueue.front();
		ErrorQueue.pop();
		MtxError.unlock();
		DriverStation::ReportError(
				"[" + std::to_string(e.time - COMP_TIME) + "] " + e.message + '\n');
		MtxError.lock();
	}
}

void DriverOutputs::sendDashboardData()
{
	while(!DashboardBooleanQueue.empty())
	{
		DashboardBoolean b = DashboardBooleanQueue.front();
		DashboardBooleanQueue.pop();
		MtxDashboard.unlock();
		SmartDashboard::PutBoolean(b.key, b.boolean);
		MtxDashboard.lock();
	}

	while(!DashboardNumberQueue.empty())
	{
		DashboardNumber n = DashboardNumberQueue.front();
		DashboardNumberQueue.pop();
		MtxDashboard.unlock();
		SmartDashboard::PutNumber(n.key, n.number);
		MtxDashboard.lock();
	}

	while(!DashboardStringQueue.empty())
	{
		DashboardString s = DashboardStringQueue.front();
		DashboardStringQueue.pop();
		MtxDashboard.unlock();
		SmartDashboard::PutString(s.key, s.string);
		MtxDashboard.lock();
	}
}

void DriverOutputs::run()
{
	while(true)
	{
		// Driver Errors
		if(UpdateErrors && DriverStation::GetInstance()->IsDSAttached())
		{
			MtxError.lock();
			UpdateErrors = false;
			sendErrors();
			MtxError.unlock();
		}

		// SmartDashboard
		if(UpdateDashboard)
		{
			MtxDashboard.lock();
			UpdateDashboard = false;
			sendDashboardData();
			MtxDashboard.unlock();
		}

		Wait(.05);
	}
}
