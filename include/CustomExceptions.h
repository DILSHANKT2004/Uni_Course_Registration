#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <stdexcept>
#include <string>

// ==========================================
// Base Exception Classes
// ==========================================
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

class StorageException : public std::runtime_error {
public:
    explicit StorageException(const std::string& msg) 
        : std::runtime_error(msg) {}
};

// ==========================================
// Member 1 Exceptions (Domain & Rules)
// ==========================================
// Thrown when course prerequisite rules are violated (FR3.2, FR3.3)
class PrerequisiteNotMetException : public EnrolmentException {
public:
    explicit PrerequisiteNotMetException(const std::string& msg = "Prerequisites for this course are not met.") 
        : EnrolmentException(msg) {}
};

// Thrown when trying to enrol in a full course (FR3.2, FR3.3)
class CourseFullException : public EnrolmentException {
public:
    explicit CourseFullException(const std::string& msg = "Course capacity has been reached.") 
        : EnrolmentException(msg) {}
};

// ==========================================
// Member 2 Exceptions (Scheduling & Attendance)
// ==========================================
class TimetableClashException : public EnrolmentException {
public:
    explicit TimetableClashException(const std::string& msg = "Timetable clash detected.") 
        : EnrolmentException(msg) {}
};

class SessionClosedException : public AttendanceException {
public:
    explicit SessionClosedException(const std::string& msg = "Attendance session is closed or expired.") 
        : AttendanceException(msg) {}
};

class NotEnrolledException : public AttendanceException {
public:
    explicit NotEnrolledException(const std::string& msg = "Student is not enrolled in this course.") 
        : AttendanceException(msg) {}
};

class DuplicateAttendanceException : public AttendanceException {
public:
    explicit DuplicateAttendanceException(const std::string& msg = "Attendance has already been recorded.") 
        : AttendanceException(msg) {}
};

// ==========================================
// Member 3 Exceptions (Persistence & File I/O)
// ==========================================
// Thrown when corrupt or missing data files are encountered (FR5.3)
class FileCorruptedException : public StorageException {
public:
    explicit FileCorruptedException(const std::string& msg = "Data file is missing or corrupted.") 
        : StorageException(msg) {}
};

#endif // CUSTOMEXCEPTIONS_H