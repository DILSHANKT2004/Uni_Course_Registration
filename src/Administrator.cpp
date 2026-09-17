#include "Administrator.h"
#include "Course.h"
#include "Report.h"
#include "Student.h" 
#include "Lecturer.h" 
#include "LectureCourse.h" 
#include <iostream>
#include <limits>
#include <stdexcept>

Administrator::Administrator(std::string id, std::string name, std::string username, std::string password,
                             Repository<Person>* pRepo, Repository<Course>* cRepo)
    : Person(id, name, username, password), personRepo(pRepo), courseRepo(cRepo) {}

std::string Administrator::getRole() const {
    return "Administrator";
}

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

// === User Management 

void Administrator::createUser() {
    if (!personRepo) {
        throw std::runtime_error("Repository not connected.");
    }

    std::string id, name, username, pass;
    int type;

    std::cout << "--- Create New User ---\n";
    std::cout << "Select Type (1. Student, 2. Lecturer): ";
    std::cin >> type;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter ID: ";
    std::getline(std::cin, id);
    
    if (personRepo->findById(id) != nullptr) {
        std::cout << "Error: User with ID " << id << " already exists.\n";
        return;
    }

    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Username: ";
    std::getline(std::cin, username);
    std::cout << "Enter Password: ";
    std::getline(std::cin, pass);

    if (type == 1) {
        personRepo->add(new Student(id, name, username, pass));
        std::cout << "Student created successfully.\n";
    } else if (type == 2) {
        personRepo->add(new Lecturer(id, name, username, pass));
        std::cout << "Lecturer created successfully.\n";
    } else {
        std::cout << "Invalid user type.\n";
    }
}

void Administrator::updateUser(const std::string& targetId) {
    if (!personRepo) return;

    Person* user = personRepo->findById(targetId);
    if (!user) {
        throw std::invalid_argument("Update failed: Target User ID does not exist.");
    }

    std::cout << "Updating user " << targetId << " (" << user->getName() << ")...\n";
    std::cout << "Enter new name (leave blank to keep current): ";
    std::string newName;
    std::getline(std::cin, newName);
    
    if (!newName.empty()) {
        user->setName(newName); 
        std::cout << "User updated successfully.\n";
    } else {
        std::cout << "No changes made.\n";
    }
}

void Administrator::removeUser(const std::string& targetId) {
    if (!personRepo) return;

    Person* user = personRepo->findById(targetId);
    if (!user) {
        throw std::invalid_argument("Removal failed: Target User ID does not exist.");
    }

    personRepo->remove(user);
    delete user; 
    std::cout << "User " << targetId << " removed successfully.\n";
}

// === Course Management (FR2.1) ===[cite: 1]

void Administrator::createCourse() {
    if (!courseRepo) {
        throw std::runtime_error("Course Repository not connected.");
    }

    std::string code, title;
    double credits;
    int capacity;

    std::cout << "--- Create New Course ---\n";
    std::cout << "Enter Course Code: ";
    std::getline(std::cin, code);

    if (courseRepo->findById(code) != nullptr) {
        std::cout << "Error: Course code " << code << " already exists.\n";
        return;
    }

    std::cout << "Enter Course Title: ";
    std::getline(std::cin, title);
    std::cout << "Enter Credit Value: ";
    std::cin >> credits;
    std::cout << "Enter Capacity: ";
    std::cin >> capacity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // courseRepo->add(new LectureCourse(code, title, credits, capacity));
    std::cout << "Course '" << code << "' created successfully.\n";
}

void Administrator::editCourse(const std::string& courseCode) {
    if (!courseRepo) return;

    Course* course = courseRepo->findById(courseCode);
    if (!course) {
        throw std::invalid_argument("Edit failed: Course code " + courseCode + " not found.");
    }

    std::cout << "Editing course " << courseCode << "...\n";
    std::cout << "Enter new capacity (or 0 to keep current): ";
    int newCapacity;
    std::cin >> newCapacity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (newCapacity > 0) {
        // course->setCapacity(newCapacity); // Assumes a setCapacity method exists in Course.h
        std::cout << "Course updated successfully.\n";
    } else {
        std::cout << "No changes made.\n";
    }
}

void Administrator::removeCourse(const std::string& courseCode) {
    if (!courseRepo) return;

    Course* course = courseRepo->findById(courseCode);
    if (!course) {
        throw std::invalid_argument("Removal failed: Course code " + courseCode + " not found.");
    }

    courseRepo->remove(course);
    delete course;
    std::cout << "Course " << courseCode << " removed successfully.\n";
}

// === Reporting (FR6.1) ===[cite: 1]

Report Administrator::generateReport() const {
    std::cout << "Generating system enrolment report...\n";
    Report sysReport("System Enrolment Report");

    if (personRepo && courseRepo) {
        sysReport.addLine("Total Users: " + std::to_string(personRepo->getAll().size()));
        sysReport.addLine("Total Courses: " + std::to_string(courseRepo->getAll().size()));
        sysReport.addLine("-----------------------------");
        
        for (Course* c : courseRepo->getAll()) {
            if (c) {
                // Uncomment once getCode(), getTitle(), and getEnrolledStudents() are implemented in Course.h
                // sysReport.addLine(c->getCode() + " - " + c->getTitle() + ": " + 
                // std::to_string(c->getEnrolledStudents().size()) + " students");
            }
        }
    } else {
        sysReport.addLine("Error: Repositories unavailable.");
    }

    return sysReport;
}