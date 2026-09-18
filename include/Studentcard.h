#ifndef STUDENTCARD_H
#define STUDENTCARD_H

#include <string>
using namespace std;

class Student;

class StudentCard {
private:
    std::string uid;
    Student* owner;

public:
    StudentCard(string uid, Student* owner);

    const string& getUid() const;
    Student* getOwner() const;
};

#endif 