#include "RunningProcesses.h"

void RunningProcesses::runProgramMonitor(const char *programMonitorPath) {
    ShellExecuteA(NULL, "open", programMonitorPath, NULL, NULL, SW_SHOW);
}

bool RunningProcesses::isProgramScanRunning() {
    std::vector<std::string> proc = getRunningProcesses();
    for(int i = 0; i < proc.size(); i++) {
        if("Program.exe" == proc[i]) {
            return true;
        }
    }

    return false;
}

char* RunningProcesses::programMonitorPath() {
    static char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH);

    return exePath;
}
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

void RunningProcesses::runOnStartup(const std::string &programName, const std::string &programPath) {
    HKEY key;

    RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &key);
    RegSetValueExA(key, programName.c_str(), 0, REG_SZ, (BYTE*)programPath.c_str(), programPath.size() + 1);
    //schedule program start to cpu with high priority
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    RegCloseKey(key);
}