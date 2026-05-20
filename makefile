EDR_FLAGS = -std=c++23 -static-libgcc -static-libstdc++ -static

Program:
	g++ Main/Main.cpp Main/Alerts.cpp Main/Menu.cpp Main/RunningProcesses.cpp Main/Vector.cpp -o Main/Program $(EDR_FLAGS)

clean:
	rm -f Main/Program

