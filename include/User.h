#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>
using namespace std;

class User{
    private:
        string username;
        string password;
        string fullname;
    public:
        User(string uname, string pass, string fname);
        
        virtual ~User()=default;

        string getUsername() const;
        string getFullName() const;
        bool checkPassword(const string &pass) const;

        virtual void displayMenu() const = 0;

};

#endif