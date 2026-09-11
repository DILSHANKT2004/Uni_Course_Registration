#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>
#include "Timetable.h"

// Forward declarations to avoid circular dependencies
class Student;
class AttendanceRegister;

class Course {
private:
    std::string code;
    std::string title;
    int creditValue;
    int capacity;

    std::vector<Course*> prerequisites;
    std::vector<Student*> enrolledStudents; // Aggregation
    
    Timetable timetable;                    // Composition (by value)[cite: 1]
    AttendanceRegister* attendanceRegister; // Composition (by pointer)[cite: 1]

public:
    // Constructor
    Course(std::string code, std::string title, int creditValue, int capacity);
    
    // Virtual destructor is mandatory for abstract base classes[cite: 1]
    virtual ~Course();

    // Rule of Three: Delete copy semantics to prevent shallow copying of the dynamic register[cite: 1]
    Course(const Course&) = delete;
    Course& operator=(const Course&) = delete;

    // Pure virtual function enforcing polymorphic grading behavior across derived types[cite: 1]
    virtual double computeGrade(double score) const = 0;

    // Core Enrolment Engine Rules[cite: 1]
    bool isFull() const;
    bool meetsPrerequisites(const Student* student) const;
    
    // Management Methods
    void addPrerequisite(Course* course);
    void enrolStudent(Student* student);
    void removeStudent(Student* student);

    // Const-correct getters[cite: 1]
    const std::string& getCode() const;
    const std::string& getTitle() const;
    const Timetable& getTimetable() const;
    const std::vector<Student*>& getEnrolledStudents() const;

    // Overloaded operators for clash detection and formatting
    bool operator==(const Course& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Course& course);
};

#endif // COURSE_H