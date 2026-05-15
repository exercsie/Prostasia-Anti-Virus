#include "Alerts.h"

int Alerts::alertBox(const char *text, const char *title, UINT flags) {
	return MessageBoxA(NULL, text, title, flags);
}

std::vector<std::string> Alerts::loadSuspiciousPrograms(const std::string& fileName) {
	std::vector<std::string> programs;

	std::ifstream file(fileName);

	if(!file.is_open()) {
		std::cout << "The file " << fileName << " is already open!\n";
		return{};
	}

	std::string line;

	while(std::getline(file, line)) {
		if(!line.empty()) {
			programs.push_back(line);
		}
	}

	file.close();

	return programs;
}

bool Alerts::isSuspicious(const std::string &fileName, std::string &outName) {
	std::vector<std::string> suspicious = loadSuspiciousPrograms("../Resources/Suspicious-Programs.txt");

	for(int i = 0; i < suspicious.size(); i++) {
		if(suspicious[i] == fileName) {
			outName = suspicious[i];
			std::cout << "Found suspicious program running: " << suspicious[i] << std::endl;
			return true;
		}
	}

	return false;
}