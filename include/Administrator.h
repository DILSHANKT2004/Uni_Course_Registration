#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include <string>
#include "User.h"
using namespace std;


class Administrator : public User {
public:
    Administrator(string id, string name, string uname, string pass);
    
    void showMenu() const override;
};

#endif