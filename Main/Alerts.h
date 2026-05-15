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
	bool isSuspicious(const std::string &fileName, std::string &outName);
	std::vector<std::string> loadSuspiciousPrograms(const std::string &fileName);
};

