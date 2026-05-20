#include "Monitor.h"

void Monitor::runOnStartup(const std::string &programName, const std::string &programPath) {
    HKEY key;

    RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &key);
    RegSetValueExA(key, programName.c_str(), 0, REG_SZ, (BYTE*)programPath.c_str(), programPath.size() + 1);
    //schedule program start to cpu with high priority
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    RegCloseKey(key);
}

void Monitor::mainAlert() {
	std::atomic<bool> alertActive = false;

	RunningProcesses processes;
	Vector v;
    Alerts alert;
	std::string suspiciousProgram;

	char *exePath = processes.getProstasiaUIPath();
	std::string exeDir = std::string(exePath);
	exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
	std::string resourcePath = exeDir + "\\..\\..\\Resources\\Suspicious-Programs.txt";

	std::vector<std::string> suspiciousList = alert.loadSuspiciousPrograms(resourcePath);
	std::vector<std::string> temp = suspiciousList;

	// run on startup
	runOnStartup("Prostasia", exePath);
	while(true) {
		bool found = alert.isSuspicious(processes.getRunningProcesses(), temp, suspiciousProgram);
		if(found) {
			alertActive = true;
			std::string message = suspiciousProgram + " is suspicious, do you want to close it?";
			int answer = alert.alertBox(message.c_str(), "Suspicious program", MB_ICONWARNING | MB_TOPMOST | MB_SETFOREGROUND  | MB_YESNO);
			switch(answer) {
				case IDYES: {
					alertActive = false;
					processes.killProcess(suspiciousProgram);
					break;
				}

				case IDNO: {
					std::string message1 = "Do you want to add an exception to " + suspiciousProgram + " in the future?";
					int answer1 = alert.alertBox(message1.c_str(), "Suspicious program", MB_ICONQUESTION | MB_TOPMOST | MB_SETFOREGROUND  | MB_YESNO);
					switch(answer1) {
						case IDYES: {
							alertActive = false;
							v.removeFromVector(suspiciousList, suspiciousProgram);
							v.removeFromVector(temp, suspiciousProgram);

							alert.saveSuspiciousProgram(resourcePath, suspiciousList);
							break;
						}

						case IDNO: {
							alertActive = false;
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
}