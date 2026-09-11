#ifndef STUDENT_H
#define STUDENT_H
using namespace std;

#include "Studentcard.h"
#include "User.h"
#include "Timetable.h" // Requires composition, so the full type is needed
#include <vector>

// Forward declaration for aggregation to minimize include dependencies
class Course; 

class Student : public User {
private:
    StudentCard* studentCard;
    vector<Course*> enrolledCourses; 
    Timetable personalTimetable;          

public:
    // Constructor passes credentials up to the base class
    Student(string id, string name, string username, string password);

    // Core Enrolment Engine Methods
    void enrol(Course* course);
    void drop(Course* course);
    // Const-correct getter for the timetable
    const Timetable& viewTimetable() const;

    // Fulfilling the abstract interface requirement
    void showMenu() const override; 
};

#endif // STUDENT_H