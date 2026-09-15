#include "Person.h"

// Constructor implementation
Person::Person(std::string Uid, std::string nam, std::string uname, std::string passwordHash)
    : id(Uid), name(nam), username(uname), password(passwordHash) {}
// Login validation
bool Person::login(const std::string& inputUsername, const std::string& inputPassword) const {
    return (username == inputUsername && password == inputPassword);
}

// Getters
std::string Person::getId() const {
    return id;
}

std::string Person::getName() const {
    return name;
}

std::string Person::getRole() const {
    return "User"; 
}