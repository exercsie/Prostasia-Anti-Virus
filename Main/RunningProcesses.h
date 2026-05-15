#include <direct.h>
#include <windows.h>
#include <tlhelp32.h>
#include <shellapi.h>
#include <string>
#include <sstream>
#include <iostream>
#include <winuser.h>
#include <vector>
#include <fstream>

class RunningProcesses {
public:
    std::vector<std::string> getRunningProcesses();
    DWORD getPID(const std::string &process);
    void killProcess(const std::string &process);
};