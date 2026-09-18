#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <string>
#include <ctime>
#include <iostream>

class Student;
class Lecturer;
class AttendanceSession;

class AttendanceRecord {
protected:
    const Student* student;
    const AttendanceSession* session;
    std::time_t timestamp;
    std::string status;        
    std::string captureMethod; 

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

#endif // ATTENDANCERECORD_H