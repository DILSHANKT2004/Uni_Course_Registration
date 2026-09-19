#include "Lecturer.h"
#include "Course.h" 
#include "Student.h"
#include "Timeslot.h"
#include "AttendanceSession.h"
#include <iostream>
#include <algorithm>
#include <atomic>
#include <ctime>
#include <stdexcept>
#include <sstream>

namespace {
std::atomic<unsigned long> nextSessionNumber{0};
}

Lecturer::Lecturer(std::string id, std::string name, std::string username, std::string password)
    : Person(id, name, username, password) {
}

std::string Lecturer::getRole() const {
    return "Lecturer";
}

const std::vector<Course*>& Lecturer::getAssignedCourses() const {
    return assignedCourses;
}

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

std::vector<Student*> Lecturer::viewEnrolledStudents(const Course& course) const {
    bool isAssigned = false;
    for (const Course* assignedCourse : assignedCourses) {
        if (assignedCourse == &course) {
            isAssigned = true;
            break;
        }
    }

    if (!isAssigned) {
        throw std::invalid_argument("Access Denied: Lecturer is not assigned to this course.");
    }

    return course.getEnrolledStudents();
}

AttendanceSession* Lecturer::openAttendanceSession(const TimeSlot& slot) {
    bool slotBelongsToAssignedCourse = false;

    for (const Course* assignedCourse : assignedCourses) {
        if (!assignedCourse) {
            continue;
        }

        const std::vector<TimeSlot>& assignedSlots = assignedCourse->getTimetable().getSlots();
        if (std::find(assignedSlots.begin(), assignedSlots.end(), slot) != assignedSlots.end()) {
            slotBelongsToAssignedCourse = true;
            break;
        }
    }

    if (!slotBelongsToAssignedCourse) {
        throw std::invalid_argument("Attendance session cannot be opened: this slot is not part of an assigned course.");
    }

    std::ostringstream sessionIdStream;
    sessionIdStream << getId() << "-" << std::time(nullptr)
                    << "-" << nextSessionNumber.fetch_add(1);

    AttendanceSession* session = new AttendanceSession(sessionIdStream.str(), slot, 10);
    session->open();
    return session;
}

void Lecturer::closeAttendanceSession(AttendanceSession& session) {
    session.close();
}

void Lecturer::assignCourse(Course* course) {
    if (course == nullptr) {
        throw std::invalid_argument("Course pointer cannot be null.");
    }

    auto it = std::find(assignedCourses.begin(), assignedCourses.end(), course);
    if (it == assignedCourses.end()) {
        assignedCourses.push_back(course);
    }
    course->setAssignedLecturer(this);
}