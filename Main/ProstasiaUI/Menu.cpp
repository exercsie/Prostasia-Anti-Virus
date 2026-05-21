#include <iostream>
#include "Menu.h"
#include "../RunningProcesses.h"
#include "../ProcessMonitor/Monitor.h"
#include "../Vector.h"
#include "../Load.h"
void Menu::options() {
    RunningProcesses rp;
    Monitor m;
    Vector v;
    Load ld;
    Alerts alert;

    int option;
    while(true) {
        std::cout << "-------------------------------\n";
        std::cout << "Welcome to Prostasia Anti-Virus C++ 1.1\n";
        std::cout << "-------------------------------\n";
        std::cout << "0 - Exit\n";
        std::cout << "1 - Toggle process monitor\n";
        std::cout << "2 - Edit suspicious .exe's\n";
        std::cout << "3 - Scan path\n";
        std::cout << "4 - Add exceptions\n"; 
        std::cin >> option;
        std::cout << "-------------------------------\n";

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
                bool isCurrentProcessRunning = m.isProgramMonitorRunning("Monitor.exe");
                if(isCurrentProcessRunning) {
                    std::cout << "Do you want to turn the process monitor off? [Y/n]\n";
                    std::cin >> option;
                    std::cout << std::endl;

                    if(*option == 'y' || *option == 'Y') {
                        rp.killProcess("Monitor.exe");
                    } else {
                        continue;
                    }

                } else {
                    std::cout << "Do you want to turn the process monitor on? [Y/n]\n";
                    std::cin >> option;

                    if(*option == 'y' || *option == 'Y') {
                        ShellExecuteA(NULL, "open", m.getMonitorPath(), NULL, NULL, SW_SHOW);
                    } else {
                        continue;
                    }
                }
                
                break;
            }

            case 2: {
                int answer;
                std::cout << "0 - Go back\n";
                std::cout << "1 - Add a suspicious file\n";
                std::cout << "2 - Remove a suspicious file\n";
                std::cin >> answer;

                switch(answer) {
                    case 0: {
                        break;
                    }
                    case 1: {

                        break;
                    }

                    case 2: {
                        std::string fileToRemove;
                        std::vector<std::string> suspiciousList = ld.loadSuspiciousPrograms(ld.loadResourcePath());
                        std::cout << "List of the suspicious files: \n";
                        std::cout << "-------------------------------\n";
                        alert.listSuspiciousFiles(suspiciousList);
                        std::cout << "-------------------------------\n";

                        std::cout << "Enter the file name you would like to remove [press enter to go back]: ";
                        std::cin.ignore(1000, '\n');
                        std::getline(std::cin, fileToRemove);
                        if(fileToRemove.empty()) {
                            break;
                        }

                        std::cout << "Removing file: " << fileToRemove << "...\n";
                        v.removeFromVector(suspiciousList, fileToRemove);
                        alert.removeSuspiciousProgram(ld.loadResourcePath(), suspiciousList);
                        std::cout << "File: " << fileToRemove << " removed\n";
                        break;
                    }
                }

                break;
            }

            case 3: {

                break;
            }
        }




    }

    
}