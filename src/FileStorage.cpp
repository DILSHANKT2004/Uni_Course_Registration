#include "FileStorage.h"
#include "StorageException.h"
#include "Student.h"
#include "Lecturer.h"       
#include "Administrator.h"   
#include "LectureCourse.h"   
#include "LabCourse.h"       
#include "ProjectCourse.h"   
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <typeinfo>

static std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

FileStorage::FileStorage(Repository<Person>* pRepo, Repository<Course>* cRepo)
    : personRepo(pRepo), courseRepo(cRepo) {}

void FileStorage::load(const std::string& path) {
    std::ifstream inFile(path);
    
    if (!inFile.is_open()) {
        throw StorageException("Failed to open file for loading: " + path);
    }

    std::string line;
    int lineCount = 0;

    while (std::getline(inFile, line)) {
        lineCount++;
        if (line.empty()) continue; 

        std::vector<std::string> tokens = parseCSVLine(line);
        if (tokens.empty()) continue;

        std::string type = tokens[0];

        try {
            if (type == "STUDENT" && tokens.size() >= 5) {
                personRepo->add(new Student(tokens[1], tokens[2], tokens[3], tokens[4]));
            } 
            else if (type == "LECTURER" && tokens.size() >= 5) {
                personRepo->add(new Lecturer(tokens[1], tokens[2], tokens[3], tokens[4]));
            } 
            else if (type == "ADMIN" && tokens.size() >= 5) {
                personRepo->add(new Administrator(
                    tokens[1], tokens[2], tokens[3], tokens[4], personRepo, courseRepo));
            }
            else if (type == "LECTURE_COURSE" && tokens.size() >= 5) {
                courseRepo->add(new LectureCourse(
                    tokens[1],
                    tokens[2],
                    std::stoi(tokens[3]),
                    std::stoi(tokens[4])));
            }
            else if (type == "SLOT" && tokens.size() >= 8) {
                Course* course = courseRepo->findById(tokens[1]);
                if (!course) {
                    throw std::invalid_argument("Course for time slot was not found.");
                }

                const int day = std::stoi(tokens[2]);
                const int startHour = std::stoi(tokens[3]);
                const int startMinute = std::stoi(tokens[4]);
                const int endHour = std::stoi(tokens[5]);
                const int endMinute = std::stoi(tokens[6]);
                if (day < 0 || day > 6 || startHour < 0 || startHour > 23 ||
                    endHour < 0 || endHour > 23 || startMinute < 0 || startMinute > 59 ||
                    endMinute < 0 || endMinute > 59) {
                    throw std::invalid_argument("Invalid time slot values.");
                }

                course->addTimeSlot(TimeSlot(
                    static_cast<DayOfWeek>(day),
                    Time{startHour, startMinute},
                    Time{endHour, endMinute},
                    tokens[7]));
            }
            else if (type == "ASSIGN" && tokens.size() >= 3) {
                Course* course = courseRepo->findById(tokens[1]);
                Person* person = personRepo->findById(tokens[2]);
                Lecturer* lecturer = dynamic_cast<Lecturer*>(person);
                if (!course || !lecturer) {
                    throw std::invalid_argument("Course or lecturer for assignment was not found.");
                }
                lecturer->assignCourse(course);
            }
            else if (type == "PREREQUISITE" && tokens.size() >= 3) {
                Course* course = courseRepo->findById(tokens[1]);
                Course* prerequisite = courseRepo->findById(tokens[2]);
                if (!course || !prerequisite) {
                    throw std::invalid_argument("Course or prerequisite was not found.");
                }
                course->addPrerequisite(prerequisite);
            }
            else if (type == "ENROL" && tokens.size() >= 3) {
                Person* person = personRepo->findById(tokens[1]);
                Student* student = dynamic_cast<Student*>(person);
                Course* course = courseRepo->findById(tokens[2]);
                if (!student || !course) {
                    throw std::invalid_argument("Student or course for enrolment was not found.");
                }
                student->enrol(course);
            }
            
            else {
                std::cerr << "Warning: Unrecognized or malformed data on line " << lineCount << "\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line " << lineCount << ": " << e.what() << "\n";
        }
    }

    inFile.close();
    std::cout << "Data successfully loaded from " << path << std::endl;
}

void FileStorage::save(const std::string& path) {
    std::ofstream outFile(path);
    
    if (!outFile.is_open()) {
        throw StorageException("Failed to open file for saving: " + path);
    }

    // Save Persons
    for (Person* p : personRepo->getAll()) {
        if (!p) continue;

        // Use dynamic_cast to identify concrete types at runtime
        if (dynamic_cast<Student*>(p)) {
            outFile << "STUDENT,";
        } 
        else if (dynamic_cast<Lecturer*>(p)) {
            outFile << "LECTURER,";
        } else if (dynamic_cast<Administrator*>(p)) {
            outFile << "ADMIN,";
        } 
        

        outFile << p->getId() << "," << p->getName() << ","
            << p->getUsername() << "," << p->getPassword() << "\n";
    }

    // Save Courses
    for (Course* c : courseRepo->getAll()) {
        if (!c) continue;

        if (dynamic_cast<LectureCourse*>(c)) {
            outFile << "LECTURE_COURSE,";
        } else if (dynamic_cast<LabCourse*>(c)) {
            outFile << "LAB_COURSE,";
        }
        
        outFile << c->getCode() << "," << c->getTitle() << "," 
                << c->getCreditValue() << "," << c->getCapacity() << "\n";

    }

    // Save timetable slots and course relationships after all course definitions.
    for (Course* c : courseRepo->getAll()) {
        if (!c) continue;

        for (const TimeSlot& slot : c->getTimetable().getSlots()) {
            outFile << "SLOT," << c->getCode() << ","
                << static_cast<int>(slot.getDay()) << ","
                << slot.getStartTime().hours << ","
                << slot.getStartTime().minutes << ","
                << slot.getEndTime().hours << ","
                << slot.getEndTime().minutes << ","
                << slot.getLocation() << "\n";
        }

        if (c->getAssignedLecturer()) {
            outFile << "ASSIGN," << c->getCode() << ","
                    << c->getAssignedLecturer()->getId() << "\n";
        }

        for (const Course* prerequisite : c->getPrerequisites()) {
            if (prerequisite) {
                outFile << "PREREQUISITE," << c->getCode() << ","
                        << prerequisite->getCode() << "\n";
            }
        }
    }

    for (Course* c : courseRepo->getAll()) {
        if (!c) continue;
        for (const Student* student : c->getEnrolledStudents()) {
            if (student) {
                outFile << "ENROL," << student->getId() << ","
                        << c->getCode() << "\n";
            }
        }
    }

    outFile.close();
    std::cout << "Data successfully saved to " << path << std::endl;
}