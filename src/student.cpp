#include "Student.h"
#include "Course.h" // Full definition required to access course methods
#include "StudentCard.h"
#include <iostream>
#include <algorithm>

 #include "EnrolmentException.h"
 #include "TimetableClashException.h"

// Constructor: Passes credentials to the Person base class and initializes the StudentCard
Student::Student(std::string id, std::string name, std::string username, std::string password)
    : Person(id, name, username, password) {
    // Dynamically allocate the owned StudentCard
    studentCard = new StudentCard("UID-" + id, this);
}

// Destructor: Clean up dynamically allocated resources (Rule of Three/Five requirement)
Student::~Student() {
    delete studentCard;
}

// Core Enrolment Engine Logic
void Student::enrol(Course* course) {
    // 1. Check if course is full [FR3.2]
     if (course->isFull()) {
       throw EnrolmentException("Enrolment failed: Course capacity reached.");
     }

    // 2. Check prerequisites [FR3.2, FR3.4]
     if (!course->meetsPrerequisites(this)) {
         throw EnrolmentException("Enrolment failed: Prerequisites not met.");
     }

    // 3. Check for timetable clashes [FR4.2]
     if (personalTimetable.hasClashWith(course->getTimetable())) {
         throw TimetableClashException("Enrolment failed: Timetable clash detected.");
     }

    // If all checks pass, register the student
    enrolledCourses.push_back(course);
    
    // Note: You will also need to merge the course's time slots into personalTimetable
    // and tell the Course object to add this student to its register.
}

// Drop a course
void Student::drop(Course* course) {
    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), course);
    if (it != enrolledCourses.end()) {
        enrolledCourses.erase(it);
        // Note: You will also need to remove the course's slots from personalTimetable
        // and tell the Course object to remove this student.
    }
}

// Const-correct getter for the timetable
const Timetable& Student::getTimetable() const {
    return personalTimetable;
}

// Polymorphic menu implementation [FR1.3]
void Student::showMenu() const {
    std::cout << "\n=== Student Dashboard ===" << std::endl;
    std::cout << "Welcome, " << getName() << "!" << std::endl;
    std::cout << "1. View Enrolled Courses\n";
    std::cout << "2. Enrol in a Course\n";
    std::cout << "3. Drop a Course\n";
    std::cout << "4. View Personal Timetable\n";
    std::cout << "5. Logout\n";
    std::cout << "Select an option: ";
    // Interactive switch-case logic handled in your UI controller
}