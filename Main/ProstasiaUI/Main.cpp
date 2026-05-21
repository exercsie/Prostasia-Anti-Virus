#include "Menu.h"
#include <windows.h>
#include "../ProcessMonitor/Monitor.h"

int main() {
	Alerts alert;
	Menu menu;
	Monitor m;

	//only open Monitor if it isn't currently open
	if(!(m.isProgramMonitorRunning("Monitor.exe"))) {
		ShellExecuteA(NULL, "open", m.getMonitorPath(), NULL, NULL, SW_SHOW);
	}

	menu.options();
	return 0;
}