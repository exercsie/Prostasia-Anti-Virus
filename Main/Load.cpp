#include "Load.h"
#include "RunningProcesses.h"

char* Load::loadProstasiaUIPath() {
    static char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH);

    return exePath;
}

char* Load::loadMonitorPath() {
	Load ld;
    static std::string fullPath;
    char *exePath = ld.loadProstasiaUIPath();
    
	std::string exeDir = std::string(exePath);
	exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
	std::string restOfDir = "\\..\\ProcessMonitor\\Monitor.exe";

    fullPath = exeDir + restOfDir;

    return fullPath.data();
}

std::string Load::loadResourcePath() {
	RunningProcesses rp;

	char *exePath = loadProstasiaUIPath();
	std::string exeDir = std::string(exePath);
	exeDir = exeDir.substr(0, exeDir.find_last_of("\\/"));
	std::string resourcePath = exeDir + "\\..\\..\\Resources\\Suspicious-Programs.txt";

	return resourcePath;
}

std::vector<std::string> Load::loadSuspiciousPrograms(const std::string &fileName) {
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