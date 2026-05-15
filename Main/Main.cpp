#include "Alerts.h"
#include "RunningProcesses.h"
#include "Vector.h"

int main() {
	Alerts alert;
	RunningProcesses processes;
	Vector v;
	std::string suspiciousProgram;

	std::vector<std::string> suspiciousList = alert.loadSuspiciousPrograms("../Resources/Suspicious-Programs.txt");
	std::vector<std::string> temp = suspiciousList;
	while(true) {
		bool found = alert.isSuspicious(processes.getRunningProcesses(), temp, suspiciousProgram);
		if(found) {
			std::string message = suspiciousProgram + " is suspicious, do you want to close it?";
			int answer = alert.alertBox(message.c_str(), "Suspicious program", MB_ICONWARNING | MB_YESNO);
			switch(answer) {
				case IDYES: {
					break;
				}

				case IDNO: {
					v.removeFromVector(temp, suspiciousProgram);
					break;
				}
			}
		}

	}

	return 0;
}