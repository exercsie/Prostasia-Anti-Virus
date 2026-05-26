#pragma once

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "RunningProcesses.h"

class Log {
public:
    void addToLog(std::unordered_map<std::string, std::vector<std::string>> &log, 
        const std::string &programName, const std::vector<std::string> &info);
    void saveLog(const std::unordered_map<std::string, std::vector<std::string>> &log, const std::string &path);
    std::vector<std::string> getInfo(const std::string &actionTaken, const std::string &suspiciousPath);
    std::string getTime();
    std::string getDate();
};