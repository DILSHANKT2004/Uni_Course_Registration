#include "StudentCard.h"
#include "Student.h" // Full definition required since it was forward-declared in the header

// Constructor utilizing a member initializer list
StudentCard::StudentCard(std::string uid, Student* owner) 
    : uid(uid), owner(owner) {
}

// Const-correct getter for the Unique ID
const std::string& StudentCard::getUid() const {
    return uid;
}

// Getter for the Student Owner pointer
Student* StudentCard::getOwner() const {
    return owner;
}