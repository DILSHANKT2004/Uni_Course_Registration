#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <stdexcept>
#include <string>

// Base Exception Hierarchy
class EnrolmentException : public std::runtime_error {
public:
    explicit EnrolmentException(const std::string& msg) 
        : std::runtime_error(msg) {}
};

class AttendanceException : public std::runtime_error {
public:
    explicit AttendanceException(const std::string& msg) 
        : std::runtime_error(msg) {}
};

// Member 2 Specific Exception Classes

// Signalled when adding a slot creates a timetable conflict (FR4.2)
class TimetableClashException : public EnrolmentException {
public:
    explicit TimetableClashException(const std::string& msg = "Timetable clash detected.") 
        : EnrolmentException(msg) {}
};

// Signalled when trying to mark attendance on a closed/expired session (FR7.2)
class SessionClosedException : public AttendanceException {
public:
    explicit SessionClosedException(const std::string& msg = "Attendance session is closed or expired.") 
        : AttendanceException(msg) {}
};

// Signalled when student attempts marking attendance without enrolment (FR7.2)
class NotEnrolledException : public AttendanceException {
public:
    explicit NotEnrolledException(const std::string& msg = "Student is not enrolled in this course.") 
        : AttendanceException(msg) {}
};

// Signalled when student tries to mark attendance more than once (FR7.2)
class DuplicateAttendanceException : public AttendanceException {
public:
    explicit DuplicateAttendanceException(const std::string& msg = "Attendance has already been recorded for this session.") 
        : AttendanceException(msg) {}
};

#endif // CUSTOMEXCEPTIONS_H