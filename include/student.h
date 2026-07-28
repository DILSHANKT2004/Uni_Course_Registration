#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
public:
    Student(std::string uname, std::string pass, std::string name);
    
    // Override the pure virtual function
    void displayMenu() const override;
};

#endif