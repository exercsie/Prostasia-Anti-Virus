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
    void removeFromVector(std::vector<std::string> &v, const std::string &key);
};