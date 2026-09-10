#include "Course.h"
#include "Student.h"
#include "AttendanceRegister.h" // Full definition required to instantiate and delete
#include <algorithm>
#include <stdexcept>

// Constructor initializes core attributes and dynamically allocates the composed AttendanceRegister
Course::Course(std::string code, std::string title, int creditValue, int capacity)
    : code(code), title(title), creditValue(creditValue), capacity(capacity) {
    // Composition: The course strictly owns this register[cite: 1]
     attendanceRegister = new AttendanceRegister(this); 
}

// Destructor cleans up dynamically allocated composition objects[cite: 1]
Course::~Course() {
    delete attendanceRegister;
}

// Checks if the current enrolment meets or exceeds the maximum capacity[cite: 1]
bool Course::isFull() const {
    return enrolledStudents.size() >= static_cast<size_t>(capacity);
}

// Validates prerequisite chains[cite: 1]
bool Course::meetsPrerequisites(const Student* student) const {
    // Note: In a full implementation, you would check if the 'student' has successfully 
    // completed all courses listed in the 'prerequisites' vector.
    // For now, assume true if there are no prerequisites.
    return prerequisites.empty();
}

void Course::addPrerequisite(Course* course) {
    if (course && std::find(prerequisites.begin(), prerequisites.end(), course) == prerequisites.end()) {
        prerequisites.push_back(course);
    }
}

// Handles the course-side enrolment logic, throwing exceptions on business rule violations[cite: 1]
void Course::enrolStudent(Student* student) {
    if (isFull()) {
        throw std::domain_error("Cannot enrol: Course " + code + " is at full capacity.");
    }
    if (!meetsPrerequisites(student)) {
        throw std::domain_error("Cannot enrol: Student has not met prerequisites for " + code + ".");
    }
    
    // Add if not already enrolled
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

// --- Getters ---

const std::string& Course::getCode() const { return code; }
const std::string& Course::getTitle() const { return title; }
const Timetable& Course::getTimetable() const { return timetable; }
const std::vector<Student*>& Course::getEnrolledStudents() const { return enrolledStudents; }

// --- Overloaded Operators ---

// Overloaded equality operator primarily to check if two course instances represent the same offering[cite: 1]
bool Course::operator==(const Course& other) const {
    return this->code == other.code;
}

// Overloaded stream insertion operator for formatted reporting[cite: 1]
std::ostream& operator<<(std::ostream& os, const Course& course) {
    os << "[" << course.code << "] " << course.title 
       << " (" << course.creditValue << " Credits) "
       << "- Capacity: " << course.enrolledStudents.size() << "/" << course.capacity;
    return os;
}