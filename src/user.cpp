#include "User.h"

User::User(std::string uname, std::string pass, std::string name)
    : username(uname), password(pass), fullname(name) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getFullName() const {
    return fullname;
}

bool User::checkPassword(const std::string& inputPass) const {
    return password == inputPass;
}


