#include "Administrator.h"

Administrator::Administrator(std::string uname, std::string pass, std::string name)
    : User(uname, pass, name) {}

void Administrator::displayMenu() const {
    std::cout << "\n=== Administrator Dashboard ===" << std::endl;
    std::cout << "Welcome, " << getFullName() << "!" << std::endl;
    std::cout << "1. Manage Users" << std::endl;
    std::cout << "2. Manage Courses" << std::endl;
    std::cout << "3. Generate Reports" << std::endl;
    std::cout << "0. Logout" << std::endl;
}