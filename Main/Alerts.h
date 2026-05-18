#include <direct.h>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <sstream>
#include <iostream>
#include <winuser.h>
#include <vector>
#include <fstream>

class Alerts {
public:
	int alertBox(const char *text, const char *title, UINT flags);
	bool isSuspicious(const std::vector<std::string> &fileName, const std::vector<std::string> &suspiciousList, std::string &outName);
	std::vector<std::string> loadSuspiciousPrograms(const std::string &fileName);
};

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