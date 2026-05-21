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
	int alertBox(const char *text, const char *title, UINT flags);
	bool isSuspicious(const std::vector<std::string> &fileName, const std::vector<std::string> &suspiciousList, std::string &outName);
	void removeSuspiciousProgram(const std::string &path, const std::vector<std::string> &list);
	void listSuspiciousFiles(const std::vector<std::string> &list);
};