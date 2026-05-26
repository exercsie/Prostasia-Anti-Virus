#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>

class Log {
public:
    void addToLog(std::unordered_map<std::string, std::vector<std::string>> &log, 
        const std::string &programName, const std::vector<std::string> &info);
    void displayLog(std::unordered_map<std::string, std::vector<std::string>> &log);
};