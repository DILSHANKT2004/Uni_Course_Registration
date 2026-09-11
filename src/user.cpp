#include "User.h"

<<<<<<< HEAD
User::User(std::string uname, std::string pass, std::string name)
    : username(uname), password(pass), fullname(name) {}

std::string User::getusername() const {
    return username;
}

std::string User::getfullname() const {
    return fullname;
}

bool User::checkpassword(const std::string& inputPass) const {
    return password == inputPass;
=======
User::User(string uid, string nam, string uname, string pass)
    : id(uid), name(nam), username(uname), passwordHash(pass) {}

//destructor
User::~User() = default;

//getName
string User::getName() const{
    return name;
}

//getId
string User::getId() const{
    return id;
}

//checkPassword
bool User::checkPassword(const string &pass) const{
    return passwordHash == pass;
>>>>>>> 4603edd6c735434cb8ad8676a44cfd1af8d51fca
}
