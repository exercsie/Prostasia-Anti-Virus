#include "Alerts.h"

int main() {
	Alerts alert;

	alert.alertBox("This program is suspicious, are you sure you want to run it?", "Suspicious program", MB_ICONWARNING | MB_YESNO);
}