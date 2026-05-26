#include <log.h>

void Log::displayLog(std::unordered_map<std::string, std::vector<std::string>> &log) {
    for(const auto &[first, inLog] : log) {
        std::cout << first << " -> ";
        for(const auto &second : inLog) {
            std::cout << second << " ";
        }
        std::cout << '\n';
    }
}

void Log::addToLog(std::unordered_map<std::string, std::vector<std::string>> &log, 
const std::string &programName, const std::vector<std::string> &info) {

    log[programName] = info;
}



    
    
