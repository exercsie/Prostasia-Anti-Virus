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

bool Alerts::removeSuspiciousProgram(const std::string &path, std::vector<std::string> &list, const std::string &fileToRemove) {
	Vector v;
	std::ofstream file(path);

	std::vector<std::string> temp = list;
	int sizeOfOriginalVec = temp.size();
	v.removeFromVector(list, fileToRemove);
	for(const std::string &program : list) {
		file << program << std::endl;
	}

	if(sizeOfOriginalVec > list.size()) {
		return true;
	}
	return false;
}

bool Alerts::addSuspiciousProgram(const std::string &path, std::vector<std::string> &list, const std::string &fileToAdd) {
	Vector v;

	if(fileToAdd.size() <= 4 || fileToAdd.substr(fileToAdd.size() - 4) != ".exe") {
		return false;
	}

	std::ofstream file(path);

	std::vector<std::string> temp = list;
	int sizeOfOriginalVec = temp.size();
	list.push_back(fileToAdd);

	for(const std::string &program : list) {
		file << program << std::endl;
	}

	if(list.size() > sizeOfOriginalVec) {
		return true;
	}

	return false;
}

void Alerts::listSuspiciousFiles(const std::vector<std::string> &list) {
	for(int i = 0; i < list.size(); i++) {
		std::cout << list.at(i) << std::endl;
	}
}