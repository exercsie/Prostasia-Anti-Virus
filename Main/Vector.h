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

class Vector {
public:
    std::vector<std::string> removeFromVector(std::vector<std::string> &v, std::string &key);
};