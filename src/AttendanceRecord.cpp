#include "AttendanceRecord.h"
#include <iomanip>

// Parametrized constructor for base AttendanceRecord
AttendanceRecord::AttendanceRecord(const Student* student, const AttendanceSession* session, 
                                   std::string status, std::string captureMethod)
    : student(student), session(session), timestamp(std::time(nullptr)), 
      status(std::move(status)), captureMethod(std::move(captureMethod)) {}

// Getters
const Student* AttendanceRecord::getStudent() const {
    return student;
}

const AttendanceSession* AttendanceRecord::getSession() const {
    return session;
}

std::time_t AttendanceRecord::getTimestamp() const {
    return timestamp;
}

std::string AttendanceRecord::getStatus() const {
    return status;
}

std::string AttendanceRecord::getCaptureMethod() const {
    return captureMethod;
}

// Stream insertion operator overload for outputting record details
std::ostream& operator<<(std::ostream& os, const AttendanceRecord& record) {
    std::tm* timeInfo = std::localtime(&record.timestamp);
    
    os << "Status: " << record.status 
       << " | Method: " << record.captureMethod 
       << " | Time: " << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
    return os;
}

// Parametrized constructor for derived CorrectionRecord
CorrectionRecord::CorrectionRecord(const Student* student, const AttendanceSession* session, 
                                   std::string status, std::string captureMethod, 
                                   const Lecturer* actingLecturer, std::string reason)
    : AttendanceRecord(student, session, std::move(status), std::move(captureMethod)),
      actingLecturer(actingLecturer), reason(std::move(reason)) {}

// Getters for CorrectionRecord
const Lecturer* CorrectionRecord::getActingLecturer() const {
    return actingLecturer;
}

std::string CorrectionRecord::getReason() const {
    return reason;
}