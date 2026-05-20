PROGRAM_FLAGS = -std=c++23 -static-libgcc -static-libstdc++ -static
MONITOR_FLAGS = -std=c++23 -mwindows -static-libgcc -static-libstdc++ -static

Monitor:
	g++ Main/ProcessMonitor/Monitor.cpp Main/ProcessMonitor/ProcessMonitor.cpp Main/RunningProcesses.cpp Main/Vector.cpp Main/Alerts.cpp -o Main/ProcessMonitor/Monitor ${MONITOR_FLAGS}

Program:
	g++ Main/Main.cpp Main/Alerts.cpp Main/Menu.cpp Main/RunningProcesses.cpp Main/Vector.cpp -o Main/Program $(PROGRAM_FLAGS)

clean:
	rm -f Main/Program
	rm -f Main/ProcessMonitor/Monitor

