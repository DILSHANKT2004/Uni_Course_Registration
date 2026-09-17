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
            else if (type == "LECTURE_COURSE" && tokens.size() >= 5) {
                courseRepo->add(new LectureCourse(
                    tokens[1],
                    tokens[2],
                    std::stoi(tokens[3]),
                    std::stoi(tokens[4])));
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

    outFile.close();
    std::cout << "Data successfully saved to " << path << std::endl;
}