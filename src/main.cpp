#include <iostream>
#include <string>

#include "Person.h"
#include "student.h"
#include "Lecturer.h"
#include "Administrator.h"

using namespace std;

int main() {

    // Create sample users
    Student student(
        "S001",
        "Alice",
        "alice",
        "1234"
    );

    Lecturer lecturer(
        "L001",
        "Dr. Smith",
        "smith",
        "1234"
    );

    Administrator administrator(
        "A001",
        "Admin User",
        "admin",
        "1234"
    );

    string username;
    string password;

    cout << "=========================================\n";
    cout << " UNIVERSITY COURSE REGISTRATION SYSTEM\n";
    cout << "=========================================\n";

    cout << "\nUsername: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    Person* currentUser = nullptr;

    // Check student
    if (student.login(username, password)) {
        currentUser = &student;
    }
    // Check lecturer
    else if (lecturer.login(username, password)) {
        currentUser = &lecturer;
    }
    // Check administrator
    else if (administrator.login(username, password)) {
        currentUser = &administrator;
    }

    // Invalid login
    else {
        cout << "\nInvalid username or password.\n";
        return 0;
    }

    cout << "\nLogin successful!\n";
    cout << "Welcome, " << currentUser->getName() << "!\n";
    cout << "Role: " << currentUser->getRole() << "\n";

    cout << "\n-----------------------------------------\n";
    currentUser->showMenu();

    return 0;
}
