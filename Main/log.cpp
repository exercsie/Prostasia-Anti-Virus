#include "log.h"

void Log::saveLog(const std::unordered_map<std::string, std::vector<std::string>> &log, const std::string &path) {
    std::ofstream file(path, std::ios::app);

    for(const auto &[programName, info] : log) {
        file << programName << " | ";
        for(const auto &entries : info) {
            file << entries << " | ";
        }

        file << '\n';
    }

    file.close();
}

void Log::addToLog(std::unordered_map<std::string, std::vector<std::string>> &log, 
const std::string &programName, const std::vector<std::string> &info) {

    log[programName] = info;
}

std::vector<std::string> Log::getInfo(const std::string &actionTaken, const std::string &suspiciousPath) {
    RunningProcesses rp;
    std::vector<std::string> info;
    info.push_back(getTime());
    info.push_back(getDate());
    info.push_back(actionTaken);
    info.push_back(suspiciousPath);

    return info;
}

std::string Log::getTime() {
    SYSTEMTIME t;

    int hour, minute, seconds;
    GetLocalTime(&t);
    hour = t.wHour;
    minute = t.wMinute;
    seconds = t.wSecond;

    std::string hourStr, minuteStr, secondStr;
    hourStr = std::to_string(hour);
    minuteStr = std::to_string(minute);
    secondStr = std::to_string(seconds);

    std::string time = hourStr + ":" + minuteStr + ":" + secondStr;
    return time;
}

std::string Log::getDate() {
    SYSTEMTIME d;

    int day, month, year;
    GetSystemTime(&d);
    day = d.wDay;
    month = d.wMonth;
    year = d.wYear;

    std::string dayStr, monthStr, yearStr;
    dayStr = std::to_string(day);
    monthStr = std::to_string(month);
    yearStr = std::to_string(year);

    std::string date = dayStr + "/" + monthStr + "/" + yearStr;
    return date;
}


    
