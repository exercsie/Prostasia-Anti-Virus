#pragma once

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

class Load {
public:
    char* loadProstasiaUIPath();
    char* loadMonitorPath();
    std::string loadResourcePath();
    std::vector<std::string> loadSuspiciousPrograms(const std::string &fileName);
    

};