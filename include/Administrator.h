#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include <string>
#include "User.h"
using namespace std;


class Administrator : public User {
public:
    Administrator(string uname, string pass, string name);
    
    void displayMenu() const override;
};

#endif