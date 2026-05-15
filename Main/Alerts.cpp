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
			if(line.back() == '\r') {
				line.pop_back();
			}
			programs.push_back(line);
		}
	}

	file.close();

	return programs;
}

bool Alerts::isSuspicious(const std::vector<std::string> &fileName, std::string &outName) {
	std::vector<std::string> suspicious = loadSuspiciousPrograms("../Resources/Suspicious-Programs.txt");

	std::cout << "Loaded " << suspicious.size() << " suspicious programs\n";
	for(int x = 0; x < suspicious.size(); x++) {
		std::cout << "Suspicious: [" << suspicious[x] << "]\n";
	} 

	for(int i = 0; i < fileName.size(); i++) {
		for(int j = 0; j < suspicious.size(); j++) {
			if(fileName[i] == suspicious[j]) {
				outName = suspicious[j];
				std::cout << "Found suspicious program running: " << suspicious[j] << std::endl;
				return true;
			}
		}
	}

	return false;
}