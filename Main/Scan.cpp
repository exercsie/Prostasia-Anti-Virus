#include "Scan.h"

bool Scan::findExe(const std::vector<std::string> &suspiciousList, const std::string &path, char result[MAX_PATH], const std::string &flags, std::vector<std::string> &foundExes) {
    bool found = false;
    std::string newPath = path + "\\";
    std::cout << "-------------------------------\n";
    std::cout << "Searching...\n";
    for(int i = 0; i < suspiciousList.size(); i++) {
        const std::string &exe = suspiciousList[i];
        HINSTANCE find = FindExecutableA(exe.c_str(), newPath.c_str(), result);

        if((INT_PTR)find > 32) {
            std::cout << "Found the file: " << exe << " in: " << result << std::endl;
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
