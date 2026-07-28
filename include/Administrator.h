#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"

class Administrator : public User {
public:
    Administrator(std::string uname, std::string pass, std::string name);
    
    void displayMenu() const override;
};

#endif