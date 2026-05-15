#include "Alerts.h"

int main() {
	Alerts alert;

	std::string suspiciousProgram;
	bool found = alert.isSuspicious("test.exe", suspiciousProgram);

	if(found) {
		std::string message = suspiciousProgram + " is suspicious, are you sure you want to run it?";
		alert.alertBox(message.c_str(), "Suspicious program", MB_ICONWARNING | MB_YESNO);
	}

}