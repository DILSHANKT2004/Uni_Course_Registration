#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected: 
    std::string id;
    std::string name;
    std::string username;
    std::string password;

public:
    Person(std::string Uid, std::string nam, std::string uname, std::string passwordHash);
    
    // Virtual destructor ensures derived classes are cleaned up correctly[cite: 1]
    virtual ~Person() = default; 

    bool login(const std::string& inputUsername, const std::string& inputPassword) const;
    
    // Pure virtual function forces derived classes to implement their own menu[cite: 1]
    virtual void showMenu() const = 0; 

    // Const-correct getters for read-only access[cite: 1]
    std::string getId() const;
    std::string getName() const;
    std::string getRole() const;
};

#endif // PERSON_H