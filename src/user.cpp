#include "User.h"

User::User(string uid, string nam, string uname, string pass)
    : id(uid), name(nam), username(uname), passwordHash(pass) {}

//destructor
User::~User() = default;

//getName
string User::getName() const{
    return name;
}

//getId
string User::getId() const{
    return id;
}

//checkPassword
bool User::checkPassword(const string &pass) const{
    return passwordHash == pass;
}
