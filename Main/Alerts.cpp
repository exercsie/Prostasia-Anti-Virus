#include "Alerts.h"

int Alerts::alertBox(const char *text, const char *title, UINT flags) {
	return MessageBoxA(NULL, text, title, flags);
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

void Alerts::removeSuspiciousProgram(const std::string &path, const std::vector<std::string> &list) {
	std::ofstream file(path);

	for(const std::string &program : list) {
		file << program << std::endl;
	}
}

void Alerts::listSuspiciousFiles(const std::vector<std::string> &list) {
	for(int i = 0; i < list.size(); i++) {
		std::cout << list.at(i) << std::endl;
	}
}