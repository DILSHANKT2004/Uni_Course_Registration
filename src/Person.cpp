#include "Person.h"

Person::Person(std::string Uid, std::string nam, std::string uname, std::string passwordHash)
    : id(Uid), name(nam), username(uname), password(passwordHash) {}

    bool Person::login(const std::string& inputUsername, const std::string& inputPassword) const {
    return (username == inputUsername && password == inputPassword);
}

std::string Person::getId() const {
    return id;
}

std::string Person::getName() const {
    return name;
}

void Person::setName(const std::string& newName) {
    name = newName;
}

std::string Person::getUsername() const {
    return username;
}

std::string Person::getPassword() const {
    return password;
}

