#include <iostream>
#include <vector>

// Since our Makefile has -Iinclude, we can just use the file names
#include "Student.h"
#include "Lecturer.h"
#include "Administrator.h"

int main() {
    // 1. Create one of each user type
    Student studentUser( "st001","Alice Smith", "stud@001","password123");
    Lecturer lecturerUser("lec001", "Dr. Bob Jones", "lec@001", "securepass");
    Administrator adminUser("adm001", "Charlie Admin", "adm@001", "adminpass");

    // 2. Create a vector of User pointers (Base class pointers)
    std::vector<User*> systemUsers;
    systemUsers.push_back(&studentUser);
    systemUsers.push_back(&lecturerUser);
    systemUsers.push_back(&adminUser);

    // 3. Test Polymorphism: The program decides which menu to show at runtime
    std::cout << "Starting System Test..." << std::endl;
    
    for (User* currentUser : systemUsers) {
        // This single line will print a different menu depending on the actual object type
        currentUser->showMenu(); 
        std::cout << "-----------------------------------" << std::endl;
    }

    return 0;
}