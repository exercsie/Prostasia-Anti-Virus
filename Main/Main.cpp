#include "Alerts.h"
#include "RunningProcesses.h"
#include "Vector.h"

int main() {
	Alerts alert;
	RunningProcesses processes;
	Vector v;
	std::string suspiciousProgram;

	char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH);
	std::string exeDir = std::string(exePath);
	exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
	std::string resourcePath = exeDir + "\\..\\Resources\\Suspicious-Programs.txt";


	std::vector<std::string> suspiciousList = alert.loadSuspiciousPrograms(resourcePath);
	std::vector<std::string> temp = suspiciousList;

	// run on startup
	processes.runOnStartup("EDR", exePath);

	while(true) {
		bool found = alert.isSuspicious(processes.getRunningProcesses(), temp, suspiciousProgram);
		if(found) {
			std::string message = suspiciousProgram + " is suspicious, do you want to close it?";
			int answer = alert.alertBox(message.c_str(), "Suspicious program", MB_ICONWARNING | MB_TOPMOST | MB_SETFOREGROUND  | MB_YESNO);
			switch(answer) {
				case IDYES: {
					processes.killProcess(suspiciousProgram);
					break;
				}

				case IDNO: {
					std::string message1 = "Do you want to add an exception to " + suspiciousProgram + " in the future?";
					int answer1 = alert.alertBox(message1.c_str(), "Suspicious program", MB_ICONQUESTION | MB_TOPMOST | MB_SETFOREGROUND  | MB_YESNO);
					switch(answer1) {
						case IDYES: {
							v.removeFromVector(suspiciousList, suspiciousProgram);
							v.removeFromVector(temp, suspiciousProgram);

							alert.saveSuspiciousProgram(resourcePath, suspiciousList);
							break;
						}

						case IDNO: {
							v.removeFromVector(temp, suspiciousProgram);
							break;
						}

					}
					break;
				}
			}
		}

		Sleep(1000);
	}

	return 0;
}