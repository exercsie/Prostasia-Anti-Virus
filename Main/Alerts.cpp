#include "Alerts.h"

int Alerts::alertBox(const char *text, const char *title, UINT flags) {
	return MessageBoxA(NULL, text, title, flags);
}

bool Alerts::isSuspicious(const std::vector<std::string> &fileName, const std::vector<std::string> &suspiciousList, std::string &outName) {
	std::unordered_set<std::string> suspiciousSet(suspiciousList.begin(), suspiciousList.end());

	for(const auto &file : fileName) {
		if(suspiciousSet.contains(file)) {
			outName = file;
			return true;
		}
	}

	return false;
}

bool Alerts::removeSuspiciousProgram(const std::string &path, std::vector<std::string> &list, const std::string &fileToRemove) {
	Vector v;
	std::ofstream file(path);

	int sizeOfOriginalVec = list.size();
	v.removeFromVector(list, fileToRemove);
	for(const std::string &program : list) {
		file << program << '\n';
	}

	return sizeOfOriginalVec > list.size();
}

bool Alerts::addSuspiciousProgram(const std::string &path, std::vector<std::string> &list, const std::string &fileToAdd) {
	Vector v;

	if(fileToAdd.size() <= 4 || fileToAdd.substr(fileToAdd.size() - 4) != ".exe") {
		return false;
	}

	std::ofstream file(path);

	int sizeOfOriginalVec = list.size();
	list.push_back(fileToAdd);

	for(const std::string &program : list) {
		file << program << '\n';
	}

	return list.size() > sizeOfOriginalVec;
}

void Alerts::listSuspiciousFiles(const std::vector<std::string> &list) {
	for(const auto &e : list) {
		std::cout << e << '\n';
	}
}