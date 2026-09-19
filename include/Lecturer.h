#ifndef LECTURER_H
#define LECTURER_H

#include "Person.h"
#include <vector>
#include <string>

// Forward declarations 
class Course;
class Student;
class TimeSlot;
class AttendanceSession;

class Lecturer : public Person {
private:
    std::vector<Course*> assignedCourses; 

public:
    Lecturer(std::string id, std::string name, std::string username, std::string password);

    void showMenu() const override;

    std::string getRole() const override;

    const std::vector<Course*>& getAssignedCourses() const;
    std::vector<Student*> viewEnrolledStudents(const Course& course) const;

    AttendanceSession* openAttendanceSession(const TimeSlot& slot);
    void closeAttendanceSession(AttendanceSession& session);

    void assignCourse(Course* course);
};

#endif 