#include "Lecturer.h"
#include "Course.h" 
#include "Student.h"
#include "Timeslot.h"
#include "AttendanceSession.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Constructor utilizing an initializer list to pass credentials to the base class
Lecturer::Lecturer(std::string id, std::string name, std::string username, std::string password)
    : Person(id, name, username, password) {
}

// Returns the role string as specified in the class diagram
std::string Lecturer::getRole() const {
    return "Lecturer";
}

// Polymorphic menu implementation for the Lecturer role[cite: 1]
void Lecturer::showMenu() const {
    std::cout << "\n=== Lecturer Dashboard ===\n";
    std::cout << "Welcome, " << getName() << "!\n";
    std::cout << "1. View Assigned Courses\n";
    std::cout << "2. View Enrolled Students for a Course\n";
    std::cout << "3. Open Attendance Session\n";
    std::cout << "4. Close Attendance Session\n";
    std::cout << "5. Logout\n";
    std::cout << "Select an option: ";
}

// Allows the lecturer to view the enrolment list of their own courses only[cite: 1]
std::vector<Student*> Lecturer::viewEnrolledStudents(const Course& course) const {
    // Verify that the course is assigned to this lecturer
    bool isAssigned = false;
    for (const Course* assignedCourse : assignedCourses) {
        if (assignedCourse == &course) {
            isAssigned = true;
            break;
        }
    }

    // Throw an exception if the business rule is violated[cite: 1]
    if (!isAssigned) {
        // You can replace std::invalid_argument with a custom exception 
        // like UnauthorizedAccessException if you have one defined in your hierarchy.
        throw std::invalid_argument("Access Denied: Lecturer is not assigned to this course.");
    }

    return course.getEnrolledStudents();
}

// Opens an attendance session for a specific time slot[cite: 1]
AttendanceSession* Lecturer::openAttendanceSession(TimeSlot& slot) {
    // Add logic here to verify the slot belongs to one of the lecturer's courses
    // before instantiating the session, throwing an exception if invalid.
    
    std::cout << "Opening attendance session...\n";
    return nullptr; 
}

// Manually closes an active attendance session[cite: 1]
void Lecturer::closeAttendanceSession(AttendanceSession& session) {
    std::cout << "Closing attendance session...\n";
    // session.setClosed(true);
}

// Helper method to assign a course to this lecturer
void Lecturer::assignCourse(Course* course) {
    auto it = std::find(assignedCourses.begin(), assignedCourses.end(), course);
    if (it == assignedCourses.end()) {
        assignedCourses.push_back(course);
    }
}