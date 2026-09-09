#include "Administrator.h"
using namespace std;

Administrator::Administrator(string id, string name, string uname, string pass )
    : User(id,name,uname,pass) {}

void Administrator::showMenu() const {
    std::cout << "\n=== Administrator Dashboard ===" << std::endl;
    std::cout << "Welcome, " << getName() << "!" << std::endl;
    std::cout << "1. Manage Users" << std::endl;
    std::cout << "2. Manage Courses" << std::endl;
    std::cout << "3. Generate Reports" << std::endl;
    std::cout << "0. Logout" << std::endl;
}