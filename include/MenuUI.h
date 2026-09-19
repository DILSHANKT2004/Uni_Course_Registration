#ifndef MENU_UI_H
#define MENU_UI_H

#include "FileStorage.h"
#include "Repository.h"

#include <string>

class Person;
class Student;
class Lecturer;
class Administrator;

class MenuUI {
private:
    Repository<Person>& personRepository;
    Repository<Course>& courseRepository;
    Storage& storage;
    std::string storagePath;

    Person* login() const;
    void showCourses() const;
    void studentMenu(Student& student);
    void lecturerMenu(Lecturer& lecturer);
    void administratorMenu(Administrator& administrator);
    void enrolCourse(Student& student);
    void dropCourse(Student& student);
    void showStudentCourses(const Student& student) const;
    void showAssignedCourses(const Lecturer& lecturer) const;
    void showLecturerEnrolment(const Lecturer& lecturer) const;
    void assignLecturerToCourse();
    void save() const;
    void createInitialAdministrator();

    static int readOption();
    static std::string readText(const std::string& prompt);

public:
    MenuUI(Repository<Person>& personRepository,
           Repository<Course>& courseRepository,
           Storage& storage,
           std::string storagePath);

    void run();
};

#endif