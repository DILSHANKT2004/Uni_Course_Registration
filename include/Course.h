#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>
#include "Timetable.h"

// Forward declarations to avoid circular dependencies
class Student;
class AttendanceRegister;
class Lecturer;

class Course {
private:
    std::string code;
    std::string title;
    int creditValue;
    int capacity;

    std::vector<Course*> prerequisites;
    std::vector<Student*> enrolledStudents; 
    Lecturer* assignedLecturer = nullptr;
    
    Timetable timetable;                   
    AttendanceRegister* attendanceRegister; 

public:
    
    Course(std::string code, std::string title, int creditValue, int capacity);
    
    virtual ~Course();

    Course(const Course&) = delete;
    Course& operator=(const Course&) = delete;

    virtual double computeGrade(double score) const = 0;

    bool isFull() const;
    bool meetsPrerequisites(const Student* student) const;
    
    void addPrerequisite(Course* course);
    void clearPrerequisites();
    void setAssignedLecturer(Lecturer* lecturer);
    void addTimeSlot(const TimeSlot& slot);
    void updateTimeSlot(std::size_t index, const TimeSlot& slot);
    void enrolStudent(Student* student);
    void removeStudent(Student* student);

    const std::string& getId() const;
    const std::string& getCode() const;
    const std::string& getTitle() const;

    int getCreditValue() const;
    int getCapacity() const;
    void setTitle(const std::string& newTitle);
    void setCreditValue(int newCreditValue);
    void setCapacity(int newCapacity);
    
    const std::vector<Course*>& getPrerequisites() const;
    Lecturer* getAssignedLecturer() const;
    const Timetable& getTimetable() const;
    const std::vector<Student*>& getEnrolledStudents() const;
    AttendanceRegister& getAttendanceRegister() const;

    bool operator==(const Course& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Course& course);
};

#endif 