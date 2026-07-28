#include "student.h"

Student::Student(std::string uname, std::string pass, std::string name)
    : User(uname, pass, name) {}
//comment
void Student::displayMenu() const {
    std::cout << "\n=== Student Dashboard ===" << std::endl;
    std::cout << "Welcome, " << getFullName() << "!" << std::endl;
    std::cout << "1. View Courses" << std::endl;
    std::cout << "2. Enrol in a Course" << std::endl;
    std::cout << "3. Drop a Course" << std::endl;
    std::cout << "4. View Timetable" << std::endl;
    std::cout << "0. Logout" << std::endl;
}