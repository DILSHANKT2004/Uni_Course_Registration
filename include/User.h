#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>
using namespace std;

class User{
    private:
        string id;
        string name;
        string username;
        string passwordHash;
        
        
    public:
        User(string uid, string nam, string uname, string pass);
        
        virtual ~User()=default;

        string getName() const;
        string getId() const;
        bool checkPassword(const string &pass) const;

        virtual void showMenu() const = 0;

};

#endif