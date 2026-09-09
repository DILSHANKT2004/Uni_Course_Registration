#ifndef LECTURER_H
#define LECTURER_H
using namespace std;

#include "User.h"
#include <vector>
#include <string>

// Forward declarations for aggregated and associated classes to prevent circular dependencies
class Course;
class Student;
class TimeSlot;
class AttendanceSession;

class Lecturer : public User {
private:
    // Aggregation: A lecturer is assigned to courses, but does not strictly own them
    std::vector<Course*> assignedCourses; 

public:
    // Constructor
    Lecturer(std::string id, std::string name, std::string username, std::string password);

    // Polymorphic dashboard implementation [FR1.3]
    void showMenu() const override;

    // Returns the role identifier as per the class diagram
    std::string getRole() const;

    // Allows the lecturer to view the enrolment list of their own courses [FR2.3]
    std::vector<Student*> viewEnrolledStudents(const Course& course) const;

    // Attendance core methods [FR7.1]
    AttendanceSession* openAttendanceSession(TimeSlot& slot);
    void closeAttendanceSession(AttendanceSession& session);

    // Helper method to add a course to the lecturer's assigned list
    void assignCourse(Course* course);
};

#endif // LECTURER_H