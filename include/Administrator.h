#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"
#include <string>

// Forward declarations for return types and parameters
class Course;
class Report;

class Administrator : public User {
public:
    // Constructor
    Administrator(std::string id, std::string name, std::string username, std::string password);

    // Polymorphic dashboard implementation
    void showMenu() const override;

    // Returns the role identifier as per the class diagram
    std::string getRole() const;

    // === User Management (FR1.2) ===
    // Note: Signatures can be expanded to take specific parameters (e.g., username, role) 
    // depending on how you implement your UI controller.
    void createUser(); 
    void updateUser(const std::string& targetId); 
    void removeUser(const std::string& targetId);

    // === Course Management (FR2.1) ===
    // The administrator manages course offerings, which can throw exceptions if 
    // business rules (like deleting a non-existent course) are violated.
    void createCourse();
    void editCourse(const std::string& courseCode);
    void removeCourse(const std::string& courseCode);

    // === Reporting (FR6.1) ===
    // Generates a system report (e.g., enrolment summary per course)[cite: 1].
    Report generateReport() const;
};

#endif // ADMINISTRATOR_H