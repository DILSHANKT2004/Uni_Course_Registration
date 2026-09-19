#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "Person.h"
#include "Repository.h"
#include "Report.h"
#include <string>

// Forward declarations
class Course;

class Administrator : public Person {
private:
    Repository<Person>* personRepo;
    Repository<Course>* courseRepo;

public:
    Administrator(std::string id, std::string name, std::string username, std::string password, 
                  Repository<Person>* pRepo = nullptr, Repository<Course>* cRepo = nullptr);
    
    ~Administrator() override = default;

    std::string getRole() const; // Identifies the role polymorphically
    void showMenu() const override;

    // User Management 
    void createUser();
    void updateUser(const std::string& targetId);
    void removeUser(const std::string& targetId);

    // Course Management 
    void createCourse();
    void editCourse(const std::string& courseCode);
    void removeCourse(const std::string& courseCode);
    void addCourseTimeSlot(const std::string& courseCode);
    void editCourseTimeSlot(const std::string& courseCode);
    void addCoursePrerequisite(const std::string& courseCode);

    // System Reports
    Report generateReport() const;
};

#endif 