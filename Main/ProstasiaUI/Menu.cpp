#include <iostream>
#include <string>
#include <sstream>
#include "Menu.h"
#include "../RunningProcesses.h"
#include "../ProcessMonitor/Monitor.h"
#include "../Vector.h"
#include "../Load.h"
#include "../Scan.h"
void Menu::options() {
    RunningProcesses rp;
    Monitor m;
    Vector v;
    Load ld;
    Alerts alert;
    Scan sc;

    int option;
    while(true) {
        std::cout << "-------------------------------\n";
        std::cout << "Welcome to Prostasia Anti-Virus C++ 1.2\n";
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
                std::cout << "3 - List suspicious files\n";
                std::cout << "4 - Open suspicious text file\n";
                std::cin >> answer;

                switch(answer) {
                    case 0: {
                        break;
                    }
                    case 1: {

                        std::string fileToAdd;
                        std::vector<std::string> suspiciousList = ld.loadSuspiciousPrograms(ld.loadResourcePath());
                        std::cout << "Enter the suspicious file to add: ";
                        std::cin.ignore(1000, '\n');
                        std::getline(std::cin, fileToAdd);
                        if(fileToAdd.empty()) {
                            break;
                        }

                        std::cout << "Adding file: " << fileToAdd << "...\n";
                        bool add = alert.addSuspiciousProgram(ld.loadResourcePath(), suspiciousList, fileToAdd);
                        if(add) {
                            std::cout << "File: " << fileToAdd << " added\n";
                            rp.restartProgram("Monitor.exe");
                            break;
                        }
                        std::cout << "File: " << fileToAdd << " is not a valid name\n";
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
                        bool removed = alert.removeSuspiciousProgram(ld.loadResourcePath(), suspiciousList, fileToRemove);
                        v.removeFromVector(suspiciousList, fileToRemove);
                        if(removed) {
                            std::cout << "File: " << fileToRemove << " removed\n";
                            rp.restartProgram("Monitor.exe");
                            break;
                        }
                        std::cout << "File: " << fileToRemove << " could not be found\n";

                        break;
                    }

                    case 3: {
                        std::cout << "List of the suspicious files: \n";
                        std::cout << "-------------------------------\n";
                        alert.listSuspiciousFiles(ld.loadSuspiciousPrograms(ld.loadResourcePath()));
                        std::cout << std::endl;
                        break;
                    }

                    case 4: {
                        std::cout << "Opening " << ld.loadResourcePath() << "...\n";
                        HINSTANCE verify = ShellExecuteA(NULL, "open", ld.loadResourcePath().c_str(), NULL, NULL, SW_SHOW);
                        if(!((INT_PTR)verify > 32)) {
                            std::cout << "Failed to open " << ld.loadResourcePath() << std::endl;
                        }

                        break;
                    }
                }

                break;
            }

            case 3: {
                int option;
                std::string path, fileName, flags;
                std::cout << "Do you want to search for an individual file or through the suspicious list text file?\n";
                std::cout << "0 - Go back\n";
                std::cout << "1 - Specific file\n";
                std::cout << "2 - Suspicious list file\n";
                std::cin >> option;

                switch(option) {
                    bool exeFound;
                    case 0: {
                        break;
                    }

                    case 1: {
                        char result[MAX_PATH];
                        std::vector<std::string> foundExes;

                        std::cout << "Enter path, file name, flags(optional[-dev]): ";

                        std::string line;
                        std::cin.ignore(1000, '\n');
                        std::getline(std::cin, line);

                        std::istringstream stream(line);

                        stream >> path >> fileName >> flags;

                        if(path.size() <= 1) {
                            std::cout << "Please input a valid path\n";
                            break;
                        }

                        if(fileName.size() <= 4 || fileName.substr(fileName.size() - 4) != ".exe") {
                            std::cout << "Please input a valid .exe\n";
                            break;
                        }

                        if(path.empty() || fileName.empty()) {
                            std::cout << "Please enter both the path and the file name\n";
                            break;
                        }

                        const std::vector<std::string> fileNameVec = { fileName };

                        exeFound = sc.findExe(fileNameVec, path, result, flags, foundExes);
                        if(exeFound) {
                            char answer;
                            std::cout << "-------------------------------\n";
                            std::cout << "Do you want to delete the following file/s [Y/n]:\n";
                            alert.listSuspiciousFiles(foundExes);
                            std::cin >> answer;
                            std::cout << std::endl;
                            std::cout << "-------------------------------\n";

                            if(answer == 'Y' || answer == 'y') {
                                std::cout << "Deleting....\n";
                                for(int i = 0; i < fileNameVec.size(); i++) {
                                    const std::string &temp = foundExes[i];
                                    if(DeleteFileA(temp.c_str())) {
                                        std::cout << "Deleted: " << temp << std::endl;
                                    } else {
                                        std::cout << "Failed to delete: " << temp << std::endl;
                                    }
                                }
                                break;
                            } else {
                                break;
                            }
                        }

                        break;
                    }

                    case 2: {
                        char result[MAX_PATH];
                        std::vector<std::string> foundExes;

                        std::cout << "Enter path, flags(optional[-dev]): ";

                        std::string line;
                        std::cin.ignore(1000, '\n');
                        std::getline(std::cin, line);

                        std::istringstream stream(line);

                        stream >> path >> flags;

                        if(path.empty()) {
                            std::cout << "Please enter the path\n";
                            break;
                        }

                        exeFound = sc.findExe(ld.loadSuspiciousPrograms(ld.loadResourcePath()), path, result, flags, foundExes);
                        if(exeFound) {
                            char answer;
                            std::cout << "-------------------------------\n";
                            std::cout << "Do you want to delete the following file/s [Y/n]:\n";
                            alert.listSuspiciousFiles(foundExes);
                            std::cin >> answer;
                            std::cout << std::endl;
                            std::cout << "-------------------------------\n";

                            if(answer == 'Y' || answer == 'y') {
                                std::cout << "Deleting....\n";
                                for(int i = 0; i < foundExes.size(); i++) {
                                    const std::string &temp = foundExes[i];
                                    if(DeleteFileA(temp.c_str())) {
                                        std::cout << "Deleted: " << temp << std::endl;
                                    } else {
                                        std::cout << "Failed to delete: " << temp << std::endl;
                                    }
                                }
                                break;
                            } else {
                                break;
                            }
                        }

                        break;
                    }
                }
            }
        }
    }




}