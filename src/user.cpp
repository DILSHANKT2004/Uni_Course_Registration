#include "User.h"

User::User(std::string uname, std::string pass, std::string name)
    : username(uname), password(pass), fullname(name) {}

std::string User::getusername() const {
    return username;
}

std::string User::getfullname() const {
    return fullname;
}

bool User::checkpassword(const std::string& inputPass) const {
    return password == inputPass;
}


