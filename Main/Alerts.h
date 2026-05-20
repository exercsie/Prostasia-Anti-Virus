#include <direct.h>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <sstream>
#include <iostream>
#include <winuser.h>
#include <vector>
#include <fstream>
#include <thread>
#include "RunningProcesses.h"
#include "Vector.h"
#include <atomic>

class Alerts {
public:
	void mainAlert();
	int alertBox(const char *text, const char *title, UINT flags);
	bool isSuspicious(const std::vector<std::string> &fileName, const std::vector<std::string> &suspiciousList, std::string &outName);
	std::vector<std::string> loadSuspiciousPrograms(const std::string &fileName);
	void saveSuspiciousProgram(const std::string &path, const std::vector<std::string> &list);
};

void Alerts::mainAlert() {
	std::atomic<bool> alertActive = false;

	RunningProcesses processes;
	Vector v;
	std::string suspiciousProgram;

	char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH);
	std::string exeDir = std::string(exePath);
	exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
	std::string resourcePath = exeDir + "\\..\\Resources\\Suspicious-Programs.txt";

	std::vector<std::string> suspiciousList = loadSuspiciousPrograms(resourcePath);
	std::vector<std::string> temp = suspiciousList;

	// run on startup
	processes.runOnStartup("EDR", exePath);
	while(true) {
		bool found = isSuspicious(processes.getRunningProcesses(), temp, suspiciousProgram);
		if(found) {
			alertActive = true;
			std::string message = suspiciousProgram + " is suspicious, do you want to close it?";
			int answer = alertBox(message.c_str(), "Suspicious program", MB_ICONWARNING | MB_TOPMOST | MB_SETFOREGROUND  | MB_YESNO);
			switch(answer) {
				case IDYES: {
					alertActive = false;
					processes.killProcess(suspiciousProgram);
					break;
				}

				case IDNO: {
					std::string message1 = "Do you want to add an exception to " + suspiciousProgram + " in the future?";
					int answer1 = alertBox(message1.c_str(), "Suspicious program", MB_ICONQUESTION | MB_TOPMOST | MB_SETFOREGROUND  | MB_YESNO);
					switch(answer1) {
						case IDYES: {
							alertActive = false;
							v.removeFromVector(suspiciousList, suspiciousProgram);
							v.removeFromVector(temp, suspiciousProgram);

							saveSuspiciousProgram(resourcePath, suspiciousList);
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

int Alerts::alertBox(const char *text, const char *title, UINT flags) {
	return MessageBoxA(NULL, text, title, flags);
}

std::vector<std::string> Alerts::loadSuspiciousPrograms(const std::string &fileName) {
	std::vector<std::string> programs;

	std::ifstream file(fileName);

	if(!file.is_open()) {
		std::cout << "The file " << fileName << " is already open!\n";
		return{};
	}

	std::string line;

	while(std::getline(file, line)) {
		if(!line.empty()) {
			if(line.back() == '\r') {
				line.pop_back();
			}
			programs.push_back(line);
		}
	}

	file.close();

	return programs;
}

bool Alerts::isSuspicious(const std::vector<std::string> &fileName, const std::vector<std::string> &suspiciousList, std::string &outName) {
	for(int i = 0; i < fileName.size(); i++) {
		for(int j = 0; j < suspiciousList.size(); j++) {
			if(fileName[i] == suspiciousList[j]) {
				outName = suspiciousList[j];
				return true;
			}
		}
	}

	return false;
}

void Alerts::saveSuspiciousProgram(const std::string &path, const std::vector<std::string> &list) {
	std::ofstream file(path);

	for(const std::string &program : list) {
		file << program << std::endl;
	}
}