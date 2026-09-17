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
    
    virtual ~Person() = default; 

    bool login(const std::string& inputUsername, const std::string& inputPassword) const;
    
    virtual void showMenu() const = 0; 

    std::string getId() const;
    std::string getName() const;
    void setName(const std::string& newName);
    std::string getUsername() const;
    std::string getPassword() const;
    virtual std::string getRole() const = 0;
};

#endif // PERSON_H