#include "Student.h"
#include "Course.h" 
#include "StudentCard.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "CustomExceptions.h"

Student::Student(std::string id, std::string name, std::string username, std::string password)
    : Person(id, name, username, password) {
    studentCard = new StudentCard("UID-" + id, this);
}

Student::~Student() {
    delete studentCard;
}

void Student::enrol(Course* course) {
    if (course == nullptr) {
        throw std::invalid_argument("Course pointer cannot be null.");
    }

    if (isEnrolledIn(course)) {
        return;
    }

    if (course->isFull()) {
        throw CourseFullException("Enrolment failed: Course capacity reached.");
    }

    if (!course->meetsPrerequisites(this)) {
        throw PrerequisiteNotMetException("Enrolment failed: Prerequisites not met.");
    }

    if (personalTimetable.hasClashWith(course->getTimetable())) {
        throw TimetableClashException("Enrolment failed: Timetable clash detected.");
    }

    enrolledCourses.push_back(course);
    course->enrolStudent(this);

    for (const auto& slot : course->getTimetable().getSlots()) {
        personalTimetable.addSlot(slot);
    }
}

void Student::drop(Course* course) {
    if (course == nullptr) {
        throw std::invalid_argument("Course pointer cannot be null.");
    }

    auto it = std::find(enrolledCourses.begin(), enrolledCourses.end(), course);
    if (it == enrolledCourses.end()) {
        return;
    }

    enrolledCourses.erase(it);
    course->removeStudent(this);

    for (const auto& slot : course->getTimetable().getSlots()) {
        personalTimetable.removeSlot(slot);
    }
}

void Student::refreshTimetable() {
    personalTimetable = Timetable();
    for (const Course* course : enrolledCourses) {
        if (!course) {
            continue;
        }
        for (const TimeSlot& slot : course->getTimetable().getSlots()) {
            personalTimetable.addSlot(slot);
        }
    }
}

bool Student::isEnrolledIn(const Course* course) const {
    return std::find(enrolledCourses.begin(), enrolledCourses.end(), course) != enrolledCourses.end();
}

const Timetable& Student::viewTimetable() const {
    return personalTimetable;
}

void Student::showMenu() const {
    std::cout << "\n=== Student Dashboard ===" << std::endl;
    std::cout << "Welcome, " << getName() << "!" << std::endl;
    std::cout << "1. View Enrolled Courses\n";
    std::cout << "2. Enrol in a Course\n";
    std::cout << "3. Drop a Course\n";
    std::cout << "4. View Personal Timetable\n";
    std::cout << "5. Mark Attendance\n";
    std::cout << "6. View Attendance History\n";
    std::cout << "7. Logout\n";
    std::cout << "Select an option: ";
}

std::string Student::getRole() const {
    return "Student";
}