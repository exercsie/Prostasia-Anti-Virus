#include "Menu.h"
#include <windows.h>
#include "../ProcessMonitor/Monitor.h"

int main() {
	Menu menu;
	Monitor m;

	ShellExecuteA(NULL, "open", m.getMonitorPath(), NULL, NULL, SW_SHOW);
	menu.options();
	return 0;
}