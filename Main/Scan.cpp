#include "Scan.h"

bool Scan::findExe(const std::vector<std::string> &suspiciousList, const std::string &path, char result[MAX_PATH], const std::string &flags, std::vector<std::string> &foundExes) {
    bool found = false;
    std::string newPath = path + "\\";
    std::cout << "-------------------------------\n";
    std::cout << "Searching...\n";
    for(const auto &suspiciousFile : suspiciousList) {
        const std::string &exe = suspiciousFile;
        HINSTANCE find = FindExecutableA(exe.c_str(), newPath.c_str(), result);

        if((INT_PTR)find > 32) {
            std::cout << "Found the file: " << exe << " in: " << result << '\n';
            foundExes.push_back(newPath + exe);
            found = true;
        } else if(flags == "-dev") {
            int error = (INT_PTR)find;
            //std::cout << "error code: " << error << std::endl;
            switch(error) {
                case 2: {
                    std::cout << exe << " was not found.\n";
                    break;
                }

                case 3: {
                    std::cout << newPath << " is invalid.\n";
                    break;
                }

                case 5: {
                    std::cout << exe << " cannot be accessed.\n";
                    break;
                }

                case 8: {
                    std::cout << "The system is out of memory or resources.\n";
                    break;
                }

            }
        }
    }

    return found;
}

bool Scan::scanMultiplePaths(const std::vector<std::string> &suspiciousList, const std::string &rootDir) {
    char result[MAX_PATH];
    for(const auto &suspiciousFile : suspiciousList) {
        const std::string &exe = suspiciousFile;
        HINSTANCE find = FindExecutableA(exe.c_str(), rootDir.c_str(), result);
    }
}
