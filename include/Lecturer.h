#ifndef LECTURER_H
#define LECTURER_H

#include "User.h"

class Lecturer : public User {
public:
    Lecturer(std::string uname, std::string pass, std::string name);
    
    void displayMenu() const override;
};

#endif