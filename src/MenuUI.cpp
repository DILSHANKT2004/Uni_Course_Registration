#include <iostream>
#include "Person.h" 
void renderDashboard(Person* currentUser) {
    std::string role = currentUser->getRole(); //[cite: 1]
    
    std::cout << "\n--- Welcome, " << role << " ---" << std::endl;
    
    if (role == "Administrator") {
        std::cout << "1. Manage Users" << std::endl;
        std::cout << "2. Manage Courses" << std::endl;
        std::cout << "3. Generate Reports" << std::endl;
    } else if (role == "Lecturer") {
        std::cout << "1. View Course Enrolments" << std::endl;
        std::cout << "2. Start Attendance Session" << std::endl;
    } else if (role == "Student") {
        std::cout << "1. Enrol in Course" << std::endl;
        std::cout << "2. View Timetable" << std::endl;
    }


}