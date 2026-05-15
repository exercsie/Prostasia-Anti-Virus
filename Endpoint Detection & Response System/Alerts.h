#pragma once
#include <direct.h>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <sstream>
#include <iostream>
#include <winuser.h>

class Alerts {
public:
	int alertBox(const char* text, const char* title, UINT flags);
};

