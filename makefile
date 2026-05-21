PROSTASIA_FLAGS = -std=c++23 -static-libgcc -static-libstdc++ -static
MONITOR_FLAGS = -std=c++23 -mwindows -static-libgcc -static-libstdc++ -static

Monitor:
	g++ Main/Scan.cpp Main/Load.cpp Main/ProcessMonitor/Monitor.cpp Main/ProcessMonitor/ProcessMonitor.cpp Main/RunningProcesses.cpp Main/Vector.cpp Main/Alerts.cpp -o Main/ProcessMonitor/Monitor ${MONITOR_FLAGS}

Prostasia:
	g++ Main/Scan.cpp Main/Load.cpp Main/ProcessMonitor/Monitor.cpp Main/ProstasiaUI/Main.cpp Main/ProstasiaUI/Menu.cpp Main/RunningProcesses.cpp Main/Vector.cpp Main/Alerts.cpp -o Main/ProstasiaUI/Prostasia $(PROSTASIA_FLAGS)

clean:
	rm -f Main/ProstasiaUI/Prostasia
	rm -f Main/ProcessMonitor/Monitor

