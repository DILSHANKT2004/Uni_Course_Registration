#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <string>
#include <ctime>
#include <iostream>

// Forward declarations to avoid circular dependencies
class Student;
class Lecturer;
class AttendanceSession;

class AttendanceRecord {
protected:
    const Student* student;
    const AttendanceSession* session;
    std::time_t timestamp;
    std::string status;        // e.g., "present", "late"
    std::string captureMethod; // e.g., "RotatingCode", "FileReplay"

public:
    // Constructors
    AttendanceRecord(const Student* student, const AttendanceSession* session, 
                     std::string status, std::string captureMethod);
    virtual ~AttendanceRecord() = default;

    // Getters (Immutable - no setters provided per FR7.3)
    const Student* getStudent() const;
    const AttendanceSession* getSession() const;
    std::time_t getTimestamp() const;
    std::string getStatus() const;
    std::string getCaptureMethod() const;

    // Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& os, const AttendanceRecord& record);
};

// Derived class representing a corrected attendance entry
class CorrectionRecord : public AttendanceRecord {
private:
    const Lecturer* actingLecturer;
    std::string reason;

public:
    CorrectionRecord(const Student* student, const AttendanceSession* session, 
                     std::string status, std::string captureMethod, 
                     const Lecturer* actingLecturer, std::string reason);

    // Getters
    const Lecturer* getActingLecturer() const;
    std::string getReason() const;
};

#endif // ATTENDANCERECORD_H