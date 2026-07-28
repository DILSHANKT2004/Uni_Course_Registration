#include "User.h"

User::User(std::string uname, std::string pass, std::string name)
    : username(uname), password(pass), fullName(name) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getFullName() const {
    return fullName;
}

bool User::checkPassword(const std::string& inputPass) const {
    return password == inputPass;
}