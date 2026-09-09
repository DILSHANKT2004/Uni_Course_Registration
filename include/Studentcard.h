#ifndef STUDENTCARD_H
#define STUDENTCARD_H

#include <string>
using namespace std;

// Forward declaration of Student to avoid circular includes
class Student;

class StudentCard {
private:
    std::string uid;
    Student* owner;

public:
    // Constructor
    StudentCard(string uid, Student* owner);

    // Const-correct getter methods for encapsulation
    const string& getUid() const;
    Student* getOwner() const;
};

#endif 