#include "MenuUI.h"

#include "Administrator.h"
#include "Course.h"
#include "CustomExceptions.h"
#include "Lecturer.h"
#include "Person.h"
#include "Student.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

MenuUI::MenuUI(Repository<Person>& personRepository,
               Repository<Course>& courseRepository,
               Storage& storage,
               std::string storagePath)
    : personRepository(personRepository),
      courseRepository(courseRepository),
      storage(storage),
      storagePath(std::move(storagePath)) {}

int MenuUI::readOption() {
    int option;
    while (!(std::cin >> option)) {
        if (std::cin.eof()) {
            return -1;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return option;
}

std::string MenuUI::readText(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

Person* MenuUI::login() const {
    const std::string username = readText("Username: ");
    const std::string password = readText("Password: ");

    for (Person* person : personRepository.getAll()) {
        if (person && person->login(username, password)) {
            return person;
        }
    }

    std::cout << "Invalid username or password.\n";
    return nullptr;
}

void MenuUI::showCourses() const {
    const std::vector<Course*> courses = courseRepository.getAll();
    if (courses.empty()) {
        std::cout << "No courses are available.\n";
        return;
    }

    std::cout << "\n=== Course Catalogue ===\n";
    for (const Course* course : courses) {
        if (course) {
            std::cout << *course << '\n';
        }
    }
}

void MenuUI::showStudentCourses(const Student& student) const {
    bool foundCourse = false;
    for (const Course* course : courseRepository.getAll()) {
        if (course && student.isEnrolledIn(course)) {
            std::cout << *course << '\n';
            foundCourse = true;
        }
    }
    if (!foundCourse) {
        std::cout << "You are not enrolled in any courses.\n";
    }
}

void MenuUI::enrolCourse(Student& student) {
    const std::string code = readText("Course code: ");
    Course* course = courseRepository.findById(code);
    if (!course) {
        std::cout << "Course not found.\n";
        return;
    }

    try {
        student.enrol(course);
        save();
        std::cout << "Enrolment successful.\n";
    } catch (const EnrolmentException& exception) {
        std::cout << exception.what() << '\n';
    } catch (const std::exception& exception) {
        std::cout << "Enrolment failed: " << exception.what() << '\n';
    }
}

void MenuUI::dropCourse(Student& student) {
    const std::string code = readText("Course code: ");
    Course* course = courseRepository.findById(code);
    if (!course) {
        std::cout << "Course not found.\n";
        return;
    }

    try {
        student.drop(course);
        save();
        std::cout << "Course dropped.\n";
    } catch (const std::exception& exception) {
        std::cout << "Unable to drop course: " << exception.what() << '\n';
    }
}

void MenuUI::studentMenu(Student& student) {
    while (true) {
        student.showMenu();
        switch (readOption()) {
        case 1:
            showStudentCourses(student);
            break;
        case 2:
            showCourses();
            enrolCourse(student);
            break;
        case 3:
            dropCourse(student);
            break;
        case 4:
            std::cout << student.viewTimetable();
            break;
        case 5:
            save();
            return;
        default:
            std::cout << "Invalid option.\n";
        }
    }
}

void MenuUI::showAssignedCourses(const Lecturer& lecturer) const {
    const std::vector<Course*>& courses = lecturer.getAssignedCourses();
    if (courses.empty()) {
        std::cout << "No courses are assigned.\n";
        return;
    }

    for (const Course* course : courses) {
        if (course) {
            std::cout << course->getCode() << " - " << course->getTitle() << '\n';
        }
    }
}

void MenuUI::showLecturerEnrolment(const Lecturer& lecturer) const {
    const std::string code = readText("Course code: ");
    Course* course = courseRepository.findById(code);
    if (!course) {
        std::cout << "Course not found.\n";
        return;
    }

    try {
        const std::vector<Student*> students = lecturer.viewEnrolledStudents(*course);
        if (students.empty()) {
            std::cout << "No students are enrolled.\n";
            return;
        }
        for (const Student* student : students) {
            if (student) {
                std::cout << student->getId() << " - " << student->getName() << '\n';
            }
        }
    } catch (const std::exception& exception) {
        std::cout << exception.what() << '\n';
    }
}

void MenuUI::assignLecturerToCourse() {
    const std::string lecturerId = readText("Lecturer ID: ");
    Person* person = personRepository.findById(lecturerId);
    Lecturer* lecturer = dynamic_cast<Lecturer*>(person);
    if (!lecturer) {
        std::cout << "Lecturer not found.\n";
        return;
    }

    const std::string courseCode = readText("Course code: ");
    Course* course = courseRepository.findById(courseCode);
    if (!course) {
        std::cout << "Course not found.\n";
        return;
    }

    lecturer->assignCourse(course);
    std::cout << "Lecturer " << lecturer->getName()
              << " assigned to course " << course->getCode() << ".\n";
}

void MenuUI::openAttendanceSession(Lecturer& lecturer) {
    const std::string courseCode = readText("Course code: ");
    Course* course = courseRepository.findById(courseCode);
    if (!course) {
        std::cout << "Course not found.\n";
        return;
    }

    const std::vector<Course*>& assignedCourses = lecturer.getAssignedCourses();
    if (std::find(assignedCourses.begin(), assignedCourses.end(), course) == assignedCourses.end()) {
        std::cout << "Access denied: Lecturer is not assigned to this course.\n";
        return;
    }

    const std::vector<TimeSlot>& slots = course->getTimetable().getSlots();
    if (slots.empty()) {
        std::cout << "No time slots are configured for this course.\n";
        return;
    }

    std::cout << "Available time slots:\n";
    for (std::size_t index = 0; index < slots.size(); ++index) {
        std::cout << index + 1 << ". " << slots[index] << '\n';
    }

    const int slotOption = readOption();
    if (slotOption < 1 || static_cast<std::size_t>(slotOption) > slots.size()) {
        std::cout << "Invalid time slot.\n";
        return;
    }

    AttendanceSession* session = lecturer.openAttendanceSession(
        slots[static_cast<std::size_t>(slotOption - 1)]);
    activeAttendanceSessions.emplace_back(session);
    std::cout << "Attendance session opened: " << session->getSessionId() << '\n';
}

void MenuUI::closeAttendanceSession(Lecturer& lecturer) {
    if (activeAttendanceSessions.empty()) {
        std::cout << "No active attendance sessions.\n";
        return;
    }

    std::cout << "Active attendance sessions:\n";
    for (std::size_t index = 0; index < activeAttendanceSessions.size(); ++index) {
        std::cout << index + 1 << ". "
                  << activeAttendanceSessions[index]->getSessionId() << '\n';
    }

    const int sessionOption = readOption();
    if (sessionOption < 1 || static_cast<std::size_t>(sessionOption) > activeAttendanceSessions.size()) {
        std::cout << "Invalid attendance session.\n";
        return;
    }

    std::unique_ptr<AttendanceSession>& session =
        activeAttendanceSessions[static_cast<std::size_t>(sessionOption - 1)];
    lecturer.closeAttendanceSession(*session);
    std::cout << "Attendance session closed: " << session->getSessionId() << '\n';
    activeAttendanceSessions.erase(activeAttendanceSessions.begin() + sessionOption - 1);
}

void MenuUI::lecturerMenu(Lecturer& lecturer) {
    while (true) {
        lecturer.showMenu();
        switch (readOption()) {
        case 1:
            showAssignedCourses(lecturer);
            break;
        case 2:
            showLecturerEnrolment(lecturer);
            break;
        case 3:
            openAttendanceSession(lecturer);
            break;
        case 4:
            closeAttendanceSession(lecturer);
            break;
        case 5:
            return;
        default:
            std::cout << "Invalid option.\n";
        }
    }
}

void MenuUI::administratorMenu(Administrator& administrator) {
    while (true) {
        administrator.showMenu();
        try {
            switch (readOption()) {
            case 1:
                administrator.createUser();
                break;
            case 2:
                administrator.updateUser(readText("User ID: "));
                break;
            case 3:
                administrator.removeUser(readText("User ID: "));
                break;
            case 4:
                administrator.createCourse();
                break;
            case 5:
                administrator.editCourse(readText("Course code: "));
                break;
            case 6:
                administrator.removeCourse(readText("Course code: "));
                break;
            case 7:
                administrator.addCourseTimeSlot(readText("Course code: "));
                break;
            case 8:
                assignLecturerToCourse();
                break;
            case 9:
                administrator.addCoursePrerequisite(readText("Course code: "));
                break;
            case 10:
                std::cout << administrator.generateReport();
                break;
            case 11:
                return;
            default:
                std::cout << "Invalid option.\n";
            }
        } catch (const std::exception& exception) {
            std::cout << "Operation failed: " << exception.what() << '\n';
        }
    }
}

void MenuUI::createInitialAdministrator() {
    std::cout << "No user accounts are loaded. Create the first administrator account.\n";
    const std::string id = readText("Administrator ID: ");
    const std::string name = readText("Name: ");
    const std::string username = readText("Username: ");
    const std::string password = readText("Password: ");

    if (id.empty() || name.empty() || username.empty() || password.empty()) {
        std::cout << "All administrator fields are required.\n";
        return;
    }

    personRepository.add(new Administrator(
        id, name, username, password, &personRepository, &courseRepository));
    std::cout << "Administrator account created.\n";
}

void MenuUI::save() const {
    try {
        storage.save(storagePath);
    } catch (const StorageException& exception) {
        std::cerr << "Unable to save data: " << exception.what() << '\n';
    }
}

void MenuUI::run() {
    std::cout << "University Course Registration System\n";
    if (personRepository.getAll().empty()) {
        createInitialAdministrator();
        if (personRepository.getAll().empty()) {
            return;
        }
    }

    while (true) {
        std::cout << "\n1. Login\n2. View courses\n3. Exit\nSelect an option: ";
        switch (readOption()) {
        case 1: {
            Person* person = login();
            if (!person) {
                break;
            }

            if (auto* student = dynamic_cast<Student*>(person)) {
                studentMenu(*student);
            } else if (auto* lecturer = dynamic_cast<Lecturer*>(person)) {
                lecturerMenu(*lecturer);
            } else if (auto* administrator = dynamic_cast<Administrator*>(person)) {
                administratorMenu(*administrator);
            }
            break;
        }
        case 2:
            showCourses();
            break;
        case 3:
        case -1:
            save();
            return;
        default:
            std::cout << "Invalid option.\n";
        }
    }
}