#include <iostream>

class Menu {
public:
    void options();
};

void Menu::options() {
    signed int option;
    std::cout << "-------------------------------\n";
    std::cout << "Welcome to Prostasia Anti-Virus\n";
    std::cout << "-------------------------------\n";
    std::cout << "1 - Scan path\n";
    std::cout << "2 - Add exceptions\n";
    std::cout << "3 - Add suspicious .exe\n";

    std::cin >> option;

}
