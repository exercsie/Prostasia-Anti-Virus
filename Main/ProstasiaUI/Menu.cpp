#include <iostream>
#include "Menu.h"
#include "../RunningProcesses.h"
#include "../ProcessMonitor/Monitor.h"
void Menu::options() {
    RunningProcesses rp;
    Monitor m;

    int option;
    while(true) {
        std::cout << "-------------------------------\n";
        std::cout << "Welcome to Prostasia Anti-Virus\n";
        std::cout << "-------------------------------\n";
        std::cout << "0 - Exit\n";
        std::cout << "1 - Toggle process monitor\n";
        std::cout << "2 - Scan path\n";
        std::cout << "3 - Add exceptions\n";
        std::cout << "4 - Add suspicious .exe\n";

        std::cin >> option;

        if(option < 0 || option > 4) {
            std::cout << "Please choose an option between 0 - 4\n";
            continue;
        }

        switch(option) {
            case 0: {
                exit(0);
                break;
            }

            case 1: {
                char option[2];
                bool isCurrentProcessRunning = m.isProgramMonitorRunning();
                if(isCurrentProcessRunning) {
                    std::cout << "Do you want to turn the process monitor off? [Y/n]\n";
                    std::cin >> option;

                    if(*option == 'y') {
                        rp.getProstasiaUIPath();
                    } else {
                        continue;
                    }

                } else {
                    std::cout << "Do you want to turn the process monitor on? [Y/n]\n";
                    std::cin >> option;

                    if(*option == 'y') {
                        ShellExecuteA(NULL, "open", m.getMonitorPath(), NULL, NULL, SW_SHOW);
                    } else {
                        continue;
                    }
                }
                
                break;
            }

            case 2: {

                break;
            }

            case 3: {

                break;
            }
        }




    }

    
}