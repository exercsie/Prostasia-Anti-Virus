#include "RunningProcesses.h"

std::vector<std::string> RunningProcesses::getRunningProcesses() {
    std::vector<std::string> processes;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(snapshot == INVALID_HANDLE_VALUE) {
        return processes;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);

    if(Process32First(snapshot, &processEntry)) {
        do {
            processes.push_back(processEntry.szExeFile);
        } while(Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);

    for(const std::string &process : processes) {
        std::cout << process << std::endl;
    }
    
    return processes;
}