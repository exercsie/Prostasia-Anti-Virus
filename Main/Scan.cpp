#include "Scan.h"

std::vector<std::string> Scan::findExe(const std::vector<std::string> &suspiciousList, const std::string &path, char result[MAX_PATH], const std::string &flags) {
    std::vector<std::string> listOfFoundFiles;
    std::cout << "-------------------------------\n";
    std::cout << "Searching...\n";
    for(int i = 0; i < suspiciousList.size(); i++) {
        const std::string &exe = suspiciousList[i];
        HINSTANCE find = FindExecutableA(exe.c_str(), path.c_str(), result);

        if((INT_PTR)find > 32) {
            std::cout << "Found the file: " << exe << " in: " << result << std::endl;
            listOfFoundFiles.push_back(exe);
        } else if(flags == "-dev") {
            int error = (INT_PTR)find;
            switch(error) {
                case 2: {
                    std::cout << exe << " was not found.\n";
                    break;
                }

                case 3: {
                    std::cout << path << " is invalid.\n";
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

    /*for(auto &search : listOfFoundFiles) {
        std::cout << search << std::endl;
    }*/

    return listOfFoundFiles;
}
