#include "Alerts.h"
#include "RunningProcesses.h"

int main() {
	Alerts alert;
	RunningProcesses processes;

	std::string suspiciousProgram;
	bool found = alert.isSuspicious(processes.getRunningProcesses(), suspiciousProgram);

	if(found) {
		std::string message = suspiciousProgram + " is suspicious, are you sure you want to run it?";
		alert.alertBox(message.c_str(), "Suspicious program", MB_ICONWARNING | MB_YESNO);
	}

	return 0;
}