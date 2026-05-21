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

class Scan {
public:
    bool findExe(const std::vector<std::string> &suspiciousList, const std::string &path, 
        char result[MAX_PATH], const std::string &flags, std::vector<std::string> &foundExes);
};