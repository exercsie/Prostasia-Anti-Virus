#include "RunningProcesses.h"
#include "Load.h"

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

    // dispaly all processes
    /*for(const std::string &process : processes) {
        std::cout << process << std::endl;
    }*/

    return processes;
}

DWORD RunningProcesses::getPID(const std::string &process) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);

    if(Process32First(snapshot, &processEntry)) {
        do {
            if(process == processEntry.szExeFile) {
                CloseHandle(snapshot);
                return processEntry.th32ProcessID;
            }
        } while(Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);
    return 0;
}

void RunningProcesses::killProcess(const std::string &process) {
    DWORD pid = getPID(process);

    HANDLE p = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    TerminateProcess(p, 0);
    CloseHandle(p);
}

void RunningProcesses::restartProgram(const std::string &programName) {
    Load ld;
    killProcess(programName);
    ShellExecuteA(NULL, "open", ld.loadMonitorPath(), NULL, NULL, SW_SHOW);
}