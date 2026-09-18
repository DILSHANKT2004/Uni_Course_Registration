#ifndef STUDENT_H
#define STUDENT_H

#include "StudentCard.h"
#include "Person.h"
#include "Timetable.h" // Requires composition, so the full type is needed
#include <vector>

class Course; 

class Student : public Person {
private:
    StudentCard* studentCard;
    std::vector<Course*> enrolledCourses; 
    Timetable personalTimetable;          

public:
    Student(string id, string name, string username, string password);
    ~Student() override;

    void enrol(Course* course);
    void drop(Course* course);
    bool isEnrolledIn(const Course* course) const;
    const Timetable& viewTimetable() const;

    void showMenu() const override; 
    std::string getRole() const override;
};

#endif 