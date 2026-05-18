EDR_FLAGS = -std=c++23 -mwindows

Program:
	g++ Main/Main.cpp -o Main/Program $(EDR_FLAGS)

clean:
	rm -f Main/Program

