#pragma once

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
#include "../RunningProcesses.h"
#include "../Vector.h"
#include "../Alerts.h"
#include <atomic>

class Monitor {
public:
    void runOnStartup(const std::string &programName, const std::string &programPath);
    void mainAlert();
};