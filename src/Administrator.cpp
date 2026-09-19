#include "Administrator.h"
#include "AttendanceRegister.h"
#include "Course.h"
#include "Report.h"
#include "Student.h" 
#include "Lecturer.h" 
#include "LectureCourse.h" 
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

Administrator::Administrator(std::string id, std::string name, std::string username, std::string password,
                             Repository<Person>* pRepo, Repository<Course>* cRepo)
    : Person(id, name, username, password), personRepo(pRepo), courseRepo(cRepo) {}

std::string Administrator::getRole() const {
    return "Administrator";
}

void Administrator::showMenu() const {
    std::cout << "\n=== Administrator Dashboard ===\n";
    std::cout << "Welcome, " << getName() << "!\n";
    std::cout << "--- User Management ---\n";
    std::cout << "1. Create User\n";
    std::cout << "2. Update User\n";
    std::cout << "3. Remove User\n";
    std::cout << "--- Course Management ---\n";
    std::cout << "4. Create Course\n";
    std::cout << "5. Edit Course\n";
    std::cout << "6. Remove Course\n";
    std::cout << "7. Add Course Time Slot\n";
    std::cout << "8. Edit Course Time Slot\n";
    std::cout << "9. Assign Lecturer to Course\n";
    std::cout << "10. Add Course Prerequisite\n";
    std::cout << "--- System Reports ---\n";
    std::cout << "11. Generate Report\n";
    std::cout << "12. Logout\n";
    std::cout << "Select an option: ";
}


void Administrator::createUser() {
    if (!personRepo) {
        throw std::runtime_error("Repository not connected.");
    }

    std::string id, name, username, pass;
    int type;

    std::cout << "--- Create New User ---\n";
    std::cout << "Select Type (1. Student, 2. Lecturer): ";
    std::cin >> type;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter ID: ";
    std::getline(std::cin, id);
    
    if (personRepo->findById(id) != nullptr) {
        std::cout << "Error: User with ID " << id << " already exists.\n";
        return;
    }

    std::cout << "Enter Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Username: ";
    std::getline(std::cin, username);
    std::cout << "Enter Password: ";
    std::getline(std::cin, pass);

    if (type == 1) {
        personRepo->add(new Student(id, name, username, pass));
        std::cout << "Student created successfully.\n";
    } else if (type == 2) {
        personRepo->add(new Lecturer(id, name, username, pass));
        std::cout << "Lecturer created successfully.\n";
    } else {
        std::cout << "Invalid user type.\n";
    }
}

void Administrator::updateUser(const std::string& targetId) {
    if (!personRepo) return;

    Person* user = personRepo->findById(targetId);
    if (!user) {
        throw std::invalid_argument("Update failed: Target User ID does not exist.");
    }

    std::cout << "Updating user " << targetId << " (" << user->getName() << ")...\n";
    std::cout << "Enter new name (leave blank to keep current): ";
    std::string newName;
    std::getline(std::cin, newName);
    
    if (!newName.empty()) {
        user->setName(newName); 
        std::cout << "User updated successfully.\n";
    } else {
        std::cout << "No changes made.\n";
    }
}

void Administrator::removeUser(const std::string& targetId) {
    if (!personRepo) return;

    Person* user = personRepo->findById(targetId);
    if (!user) {
        throw std::invalid_argument("Removal failed: Target User ID does not exist.");
    }

    if (auto* student = dynamic_cast<Student*>(user)) {
        for (Course* course : courseRepo->getAll()) {
            if (course && student->isEnrolledIn(course)) {
                student->drop(course);
            }
        }
    }

    personRepo->remove(user);
    std::cout << "User " << targetId << " removed successfully.\n";
}


void Administrator::createCourse() {
    if (!courseRepo) {
        throw std::runtime_error("Course Repository not connected.");
    }

    std::string code, title;
    int credits;
    int capacity;

    std::cout << "--- Create New Course ---\n";
    std::cout << "Enter Course Code: ";
    std::getline(std::cin, code);

    if (courseRepo->findById(code) != nullptr) {
        std::cout << "Error: Course code " << code << " already exists.\n";
        return;
    }

    std::cout << "Enter Course Title: ";
    std::getline(std::cin, title);
    std::cout << "Enter Credit Value: ";
    std::cin >> credits;
    std::cout << "Enter Capacity: ";
    std::cin >> capacity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (credits <= 0 || capacity < 0) {
        std::cout << "Invalid course values. Course was not created.\n";
        return;
    }

    std::cout << "Prerequisite course codes (comma-separated, or NONE): ";
    std::string prerequisiteInput;
    std::getline(std::cin, prerequisiteInput);

    std::vector<Course*> prerequisites;
    if (prerequisiteInput != "NONE" && !prerequisiteInput.empty()) {
        std::stringstream prerequisiteStream(prerequisiteInput);
        std::string prerequisiteCode;
        while (std::getline(prerequisiteStream, prerequisiteCode, ',')) {
            if (prerequisiteCode.empty() || prerequisiteCode == code) {
                std::cout << "Invalid prerequisite. Course was not created.\n";
                return;
            }

            Course* prerequisite = courseRepo->findById(prerequisiteCode);
            if (!prerequisite) {
                std::cout << "Prerequisite course " << prerequisiteCode
                          << " was not found. Course was not created.\n";
                return;
            }
            prerequisites.push_back(prerequisite);
        }
    }

    auto* newCourse = new LectureCourse(code, title, credits, capacity);
    for (Course* prerequisite : prerequisites) {
        newCourse->addPrerequisite(prerequisite);
    }
    courseRepo->add(newCourse);
    std::cout << "Course '" << code << "' created successfully.\n";
}

void Administrator::editCourse(const std::string& courseCode) {
    if (!courseRepo) return;

    Course* course = courseRepo->findById(courseCode);
    if (!course) {
        throw std::invalid_argument("Edit failed: Course code " + courseCode + " not found.");
    }

    std::cout << "Editing course " << courseCode << "...\n";
    std::cout << "Enter new title (leave blank to keep current): ";
    std::string newTitle;
    std::getline(std::cin, newTitle);

    std::cout << "Enter new credit value (or 0 to keep current): ";
    int newCredits;
    std::cin >> newCredits;
    std::cout << "Enter new capacity (or 0 to keep current): ";
    int newCapacity;
    std::cin >> newCapacity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter lecturer ID (leave blank to keep current, or NONE to unassign): ";
    std::string lecturerId;
    std::getline(std::cin, lecturerId);

    bool changed = false;
    if (!newTitle.empty()) {
        course->setTitle(newTitle);
        changed = true;
    }
    if (newCredits > 0) {
        course->setCreditValue(newCredits);
        changed = true;
    }
    if (newCapacity > 0) {
        course->setCapacity(newCapacity);
        changed = true;
    }

    if (!lecturerId.empty()) {
        Lecturer* newLecturer = nullptr;
        if (lecturerId != "NONE") {
            Person* person = personRepo ? personRepo->findById(lecturerId) : nullptr;
            newLecturer = dynamic_cast<Lecturer*>(person);
            if (!newLecturer) {
                throw std::invalid_argument("Lecturer ID does not identify a lecturer.");
            }
        }

        Lecturer* currentLecturer = course->getAssignedLecturer();
        if (currentLecturer) {
            currentLecturer->unassignCourse(course);
        }

        if (newLecturer) {
            newLecturer->assignCourse(course);
        }
        changed = true;
    }

    std::cout << "Prerequisite course codes (leave blank to keep current, comma-separated to replace, or NONE to clear): ";
    std::string prerequisiteInput;
    std::getline(std::cin, prerequisiteInput);
    if (!prerequisiteInput.empty()) {
        std::vector<Course*> prerequisites;
        if (prerequisiteInput != "NONE") {
            std::stringstream prerequisiteStream(prerequisiteInput);
            std::string prerequisiteCode;
            while (std::getline(prerequisiteStream, prerequisiteCode, ',')) {
                if (prerequisiteCode.empty() || prerequisiteCode == courseCode) {
                    throw std::invalid_argument("Invalid prerequisite course code.");
                }

                Course* prerequisite = courseRepo->findById(prerequisiteCode);
                if (!prerequisite) {
                    throw std::invalid_argument("Prerequisite course " + prerequisiteCode + " was not found.");
                }
                prerequisites.push_back(prerequisite);
            }
        }

        course->clearPrerequisites();
        for (Course* prerequisite : prerequisites) {
            course->addPrerequisite(prerequisite);
        }
        changed = true;
    }

    if (changed) {
        std::cout << "Course updated successfully.\n";
    } else {
        std::cout << "No changes made.\n";
    }
}

void Administrator::removeCourse(const std::string& courseCode) {
    if (!courseRepo) return;

    Course* course = courseRepo->findById(courseCode);
    if (!course) {
        throw std::invalid_argument("Removal failed: Course code " + courseCode + " not found.");
    }

    courseRepo->remove(course);
    std::cout << "Course " << courseCode << " removed successfully.\n";
}

void Administrator::addCourseTimeSlot(const std::string& courseCode) {
    if (!courseRepo) return;

    Course* course = courseRepo->findById(courseCode);
    if (!course) {
        throw std::invalid_argument("Time slot setup failed: Course code " + courseCode + " not found.");
    }

    int day;
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    std::string location;

    std::cout << "Day (1 Monday - 7 Sunday): ";
    std::cin >> day;
    std::cout << "Start hour (0-23): ";
    std::cin >> startHour;
    std::cout << "Start minute (0-59): ";
    std::cin >> startMinute;
    std::cout << "End hour (0-23): ";
    std::cin >> endHour;
    std::cout << "End minute (0-59): ";
    std::cin >> endMinute;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Location: ";
    std::getline(std::cin, location);

    if (day < 1 || day > 7 || startHour < 0 || startHour > 23 ||
        endHour < 0 || endHour > 23 || startMinute < 0 || startMinute > 59 ||
        endMinute < 0 || endMinute > 59 ||
        Time{endHour, endMinute} <= Time{startHour, startMinute}) {
        throw std::invalid_argument("Invalid time slot values.");
    }

    const DayOfWeek selectedDay = static_cast<DayOfWeek>(day - 1);
    course->addTimeSlot(TimeSlot(
        selectedDay,
        Time{startHour, startMinute},
        Time{endHour, endMinute},
        location));
    std::cout << "Time slot added to course " << courseCode << ".\n";
}

void Administrator::editCourseTimeSlot(const std::string& courseCode) {
    if (!courseRepo) return;

    Course* course = courseRepo->findById(courseCode);
    if (!course) {
        throw std::invalid_argument("Time slot edit failed: Course code " + courseCode + " not found.");
    }

    const std::vector<TimeSlot>& slots = course->getTimetable().getSlots();
    if (slots.empty()) {
        std::cout << "No time slots are configured for this course.\n";
        return;
    }

    std::cout << "Current time slots:\n";
    for (std::size_t index = 0; index < slots.size(); ++index) {
        std::cout << index + 1 << ". " << slots[index] << '\n';
    }

    int slotNumber;
    std::cout << "Select time slot to edit: ";
    std::cin >> slotNumber;

    int day;
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    std::string location;

    std::cout << "Day (1 Monday - 7 Sunday): ";
    std::cin >> day;
    std::cout << "Start hour (0-23): ";
    std::cin >> startHour;
    std::cout << "Start minute (0-59): ";
    std::cin >> startMinute;
    std::cout << "End hour (0-23): ";
    std::cin >> endHour;
    std::cout << "End minute (0-59): ";
    std::cin >> endMinute;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Location: ";
    std::getline(std::cin, location);

    if (slotNumber < 1 || static_cast<std::size_t>(slotNumber) > slots.size() ||
        day < 1 || day > 7 || startHour < 0 || startHour > 23 ||
        endHour < 0 || endHour > 23 || startMinute < 0 || startMinute > 59 ||
        endMinute < 0 || endMinute > 59 ||
        Time{endHour, endMinute} <= Time{startHour, startMinute}) {
        throw std::invalid_argument("Invalid time slot values.");
    }

    course->updateTimeSlot(
        static_cast<std::size_t>(slotNumber - 1),
        TimeSlot(static_cast<DayOfWeek>(day - 1),
                 Time{startHour, startMinute},
                 Time{endHour, endMinute},
                 location));
    std::cout << "Time slot updated for course " << courseCode << ".\n";
}

void Administrator::addCoursePrerequisite(const std::string& courseCode) {
    if (!courseRepo) return;

    Course* course = courseRepo->findById(courseCode);
    std::string prerequisiteCode;
    std::cout << "Prerequisite course code: ";
    std::getline(std::cin, prerequisiteCode);
    Course* prerequisite = courseRepo->findById(prerequisiteCode);
    if (!course || !prerequisite) {
        throw std::invalid_argument("Course or prerequisite was not found.");
    }
    course->addPrerequisite(prerequisite);
    std::cout << "Prerequisite added to course " << courseCode << ".\n";
}


Report Administrator::generateReport() const {
    Report sysReport("System Course and Attendance Report");

    if (personRepo && courseRepo) {
        std::size_t studentCount = 0;
        std::size_t lecturerCount = 0;
        for (Person* person : personRepo->getAll()) {
            if (dynamic_cast<Student*>(person)) {
                ++studentCount;
            } else if (dynamic_cast<Lecturer*>(person)) {
                ++lecturerCount;
            }
        }

        sysReport.addLine("Total Users: " + std::to_string(personRepo->getAll().size()));
        sysReport.addLine("Total Students: " + std::to_string(studentCount));
        sysReport.addLine("Total Lecturers: " + std::to_string(lecturerCount));
        sysReport.addLine("Total Courses: " + std::to_string(courseRepo->getAll().size()));
        sysReport.addLine("-----------------------------");
        
        for (Course* c : courseRepo->getAll()) {
            if (!c) {
                continue;
            }

            sysReport.addLine(c->getCode() + " - " + c->getTitle());
            sysReport.addLine("  Credits: " + std::to_string(c->getCreditValue()));
            sysReport.addLine("  Capacity: " + std::to_string(c->getEnrolledStudents().size()) +
                              "/" + std::to_string(c->getCapacity()));
            sysReport.addLine("  Lecturer: " +
                              (c->getAssignedLecturer() ? c->getAssignedLecturer()->getName() : "Unassigned"));

            std::string prerequisites = "  Prerequisites: ";
            if (c->getPrerequisites().empty()) {
                prerequisites += "None";
            } else {
                for (std::size_t index = 0; index < c->getPrerequisites().size(); ++index) {
                    if (index > 0) {
                        prerequisites += ", ";
                    }
                    prerequisites += c->getPrerequisites()[index]->getCode();
                }
            }
            sysReport.addLine(prerequisites);
            sysReport.addLine("  Scheduled slots: " +
                              std::to_string(c->getTimetable().getSlots().size()));
            sysReport.addLine("  Attendance records: " +
                              std::to_string(c->getAttendanceRegister().getRecords().size()));
        }
    } else {
        sysReport.addLine("Error: Repositories unavailable.");
    }

    return sysReport;
}