#include "Course.h"
#include "Lecturer.h"
#include "Student.h"
#include "AttendanceRegister.h" 
#include "CustomExceptions.h"
#include <algorithm>
#include <stdexcept>

namespace {
bool prerequisitesMet(const Course& course, const Student* student,
                      std::vector<const Course*>& visited) {
    if (!student) {
        return false;
    }

    if (std::find(visited.begin(), visited.end(), &course) != visited.end()) {
        return false;
    }
    visited.push_back(&course);

    for (Course* prerequisite : course.getPrerequisites()) {
        if (!prerequisite || !student->isEnrolledIn(prerequisite) ||
            !prerequisitesMet(*prerequisite, student, visited)) {
            return false;
        }
    }

    visited.pop_back();
    return true;
}
}

Course::Course(std::string code, std::string title, int creditValue, int capacity)
    : code(code), title(title), creditValue(creditValue), capacity(capacity) {
    if (code.empty()) {
        throw std::invalid_argument("Course code cannot be empty.");
    }
    if (creditValue <= 0) {
        throw std::invalid_argument("Course credit value must be positive.");
    }
    if (capacity < 0) {
        throw std::invalid_argument("Course capacity cannot be negative.");
    }

    attendanceRegister = new AttendanceRegister();
}

Course::~Course() {
    delete attendanceRegister;
}

bool Course::isFull() const {
    return enrolledStudents.size() >= static_cast<std::size_t>(capacity);
}

bool Course::meetsPrerequisites(const Student* student) const {
    std::vector<const Course*> visited;
    return prerequisitesMet(*this, student, visited);
}

void Course::addPrerequisite(Course* course) {
    if (course == this) {
        throw std::invalid_argument("A course cannot be its own prerequisite.");
    }

    if (course && std::find(prerequisites.begin(), prerequisites.end(), course) == prerequisites.end()) {
        prerequisites.push_back(course);
    }
}

void Course::clearPrerequisites() {
    prerequisites.clear();
}

void Course::setAssignedLecturer(Lecturer* lecturer) {
    assignedLecturer = lecturer;
}

void Course::addTimeSlot(const TimeSlot& slot) {
    timetable.addSlot(slot);
}

void Course::updateTimeSlot(std::size_t index, const TimeSlot& slot) {
    timetable.updateSlot(index, slot);
}

void Course::enrolStudent(Student* student) {
    if (!student) {
        throw EnrolmentException("Cannot enrol a null student.");
    }

    if (isFull()) {
        throw CourseFullException("Cannot enrol: Course " + code + " is at full capacity.");
    }
    if (!meetsPrerequisites(student)) {
        throw PrerequisiteNotMetException(
            "Cannot enrol: Student has not met prerequisites for " + code + ".");
    }
    
    if (std::find(enrolledStudents.begin(), enrolledStudents.end(), student) == enrolledStudents.end()) {
        enrolledStudents.push_back(student);
    }
}

void Course::removeStudent(Student* student) {
    auto it = std::find(enrolledStudents.begin(), enrolledStudents.end(), student);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);
    }
}


const std::string& Course::getId() const 
    { return code; }

const std::string& Course::getCode() const
    { return code; }

const std::string& Course::getTitle() const 
    { return title; }

int Course::getCreditValue() const 
    { return creditValue; }

int Course::getCapacity() const
     { return capacity; }

void Course::setTitle(const std::string& newTitle) {
    if (newTitle.empty()) {
        throw std::invalid_argument("Course title cannot be empty.");
    }
    title = newTitle;
}

void Course::setCreditValue(int newCreditValue) {
    if (newCreditValue <= 0) {
        throw std::invalid_argument("Course credit value must be positive.");
    }
    creditValue = newCreditValue;
}

void Course::setCapacity(int newCapacity) {
    if (newCapacity < 0) {
        throw std::invalid_argument("Course capacity cannot be negative.");
    }
    if (static_cast<std::size_t>(newCapacity) < enrolledStudents.size()) {
        throw std::invalid_argument("New capacity cannot be smaller than the current enrolled count.");
    }
    capacity = newCapacity;
}

const Timetable& Course::getTimetable() const
     { return timetable; }

const std::vector<Student*>& Course::getEnrolledStudents() const 
    { return enrolledStudents; }

AttendanceRegister& Course::getAttendanceRegister() const
    { return *attendanceRegister; }


bool Course::operator==(const Course& other) const {
    return this->code == other.code;
}

std::ostream& operator<<(std::ostream& os, const Course& course) {
    os << "[" << course.code << "] " << course.title 
       << " (" << course.creditValue << " Credits) "
       << "- Capacity: " << course.enrolledStudents.size() << "/" << course.capacity;
    if (course.assignedLecturer) {
        os << " - Lecturer: " << course.assignedLecturer->getName();
    } else {
        os << " - Lecturer: Unassigned";
    }
    os << " - Prerequisites: ";
    if (course.prerequisites.empty()) {
        os << "None";
    } else {
        for (std::size_t index = 0; index < course.prerequisites.size(); ++index) {
            if (index > 0) {
                os << ", ";
            }
            os << course.prerequisites[index]->getCode();
        }
    }
    return os;
}

const std::vector<Course*>& Course::getPrerequisites() const 
    { return prerequisites; }

Lecturer* Course::getAssignedLecturer() const
    { return assignedLecturer; }