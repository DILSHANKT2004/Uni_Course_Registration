#include "../include/Lecturer.h"

Lecturer::Lecturer(std::string uname, std::string pass, std::string name)
    : User(uname, pass, name) {}

void Lecturer::displayMenu() const {
    std::cout << "\n=== Lecturer Dashboard ===" << std::endl;
    std::cout << "Welcome, " << getFullName() << "!" << std::endl;
    std::cout << "1. View My Courses" << std::endl;
    std::cout << "2. View Enrolment Lists" << std::endl;
    std::cout << "3. Manage Attendance" << std::endl;
    std::cout << "0. Logout" << std::endl;
}