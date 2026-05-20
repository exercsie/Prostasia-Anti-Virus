#include "Alerts.h"
#include <thread>
#include <atomic>
#include "Menu.h"

int main() {
	Alerts alert;
	Menu menu;

	std::thread monitor(&Alerts::mainAlert, &alert);
	menu.options();


	monitor.join();
	return 0;
}