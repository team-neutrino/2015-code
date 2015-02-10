#include "WPILib.h"
#include <thread>
#include <string>
#include <mutex>
#include <queue>

#pragma once

class DriverOutputs
{
public:
	static void init();
	static void ReportError(std::string error);

	static void UpdateSmartDashboardBoolean(std::string key, bool boolean);
	static void UpdateSmartDashboardNumber(std::string key, double number);
	static void UpdateSmartDashboardString(std::string key, std::string string);

private:
	static const double COMP_TIME;
	static void sendErrors();
	static void sendDashboardData();

	static void run();

	static void updateName();

	const double REFRESH_RATE = 5;

	struct Error
	{
		double time;
		std::string message;
	};

	struct DashboardBoolean
	{
		std::string key;
		bool boolean;
	};

	struct DashboardNumber
	{
		std::string key;
		double number;
	};

	struct DashboardString
	{
		std::string key;
		std::string string;
	};

	static bool UpdateErrors;
	static std::queue<Error> ErrorQueue;
	static std::mutex MtxError;

	static bool UpdateDashboard;
	static std::queue<DashboardBoolean> DashboardBooleanQueue;
	static std::queue<DashboardNumber> DashboardNumberQueue;
	static std::queue<DashboardString> DashboardStringQueue;
	static std::mutex MtxDashboard;

	static std::thread Thread;
};
