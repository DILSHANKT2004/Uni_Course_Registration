#include "Administrator.h"
#include "Course.h" // Required if you manipulate Course objects directly
#include "Report.h" // Required to return a Report object by value
#include <iostream>
#include <stdexcept>

// Constructor utilizing an initializer list to pass credentials to the base class
Administrator::Administrator(std::string id, std::string name, std::string username, std::string password)
    : User(id, name, username, password) {
}

// Returns the role string as specified in the class diagram


// Polymorphic menu implementation for the Administrator role[cite: 1]
void Administrator::showMenu() const {
    std::cout << "\n=== Administrator Dashboard ===\n";
    std::cout << "Welcome, " << getName() << "!\n";
    std::cout << "--- User Management ---\n";
    std::cout << "1. Create User\n";
    std::cout << "2. Update User\n";
    std::cout << "3. Remove User\n";
    std::cout << "--- Course Management ---\n";
    std::cout << "4. Create Course\n";
    std::cout << "5. Edit Course\n";
    std::cout << "6. Remove Course\n";
    std::cout << "--- System Reports ---\n";
    std::cout << "7. Generate Report\n";
    std::cout << "8. Logout\n";
    std::cout << "Select an option: ";
}

// === User Management (FR1.2) ===[cite: 1]

void Administrator::createUser() {
    std::cout << "Initiating user creation workflow...\n";
    //Instantiate a new user (Student, Lecturer, or Administrator) and add to Repository   
}

void Administrator::updateUser(const std::string& targetId) {
    // Simulated check - in reality, query your Repository<Person>
    bool userExists = false; 
    
    if (!userExists) {
        throw std::invalid_argument("Update failed: Target User ID does not exist.");
    }
    std::cout << "Updating user " << targetId << "...\n";
}

void Administrator::removeUser(const std::string& targetId) {
    // Simulated check
    bool userExists = false; 
    
    if (!userExists) {
        throw std::invalid_argument("Removal failed: Target User ID does not exist.");
    }
    std::cout << "Removing user " << targetId << "...\n";
    // Logic to delete the user and update the Repository
}

// === Course Management (FR2.1) ===[cite: 1]

void Administrator::createCourse() {
    std::cout << "Initiating course creation workflow...\n";
    // Logic to instantiate a Course (Lab, Lecture, or Project) and add to Repository
}

void Administrator::editCourse(const std::string& courseCode) {
    // Simulated check - in reality, query your Repository<Course>
    bool courseExists = false;

    if (!courseExists) {
        throw std::invalid_argument("Edit failed: Course code " + courseCode + " not found.");
    }
    std::cout << "Editing course " << courseCode << "...\n";
}

void Administrator::removeCourse(const std::string& courseCode) {
    // Simulated check
    bool courseExists = false;

    if (!courseExists) {
        throw std::invalid_argument("Removal failed: Course code " + courseCode + " not found.");
    }
    std::cout << "Removing course " << courseCode << "...\n";
}

// === Reporting (FR6.1) ===[cite: 1]


Report Administrator::generateReport() const {
    std::cout << "Generating system enrolment report...\n";
    Report sysReport("System Enrolment Report");
    // Compile data from repositories and format into the Report object
    return sysReport;
}
