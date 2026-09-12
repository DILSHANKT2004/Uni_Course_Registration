#ifndef ATTENDANCEREGISTER_H
#define ATTENDANCEREGISTER_H

#include "AttendanceRecord.h"
#include "AttendanceSession.h"
#include "AttendanceCapture.h"
#include "CustomExceptions.h"
#include <vector>
#include <string>

// Forward declarations
class Student;
class Lecturer;
class Report;

class AttendanceRegister {
private:
    std::vector<AttendanceRecord*> records; // Composition of attendance history
    std::vector<AttendanceSession> sessions;

public:
    // Constructor and Destructor (Rule of Three/Five for dynamic pointers)
    AttendanceRegister() = default;
    ~AttendanceRegister();

    // Prevent copying to avoid double deletion of records
    AttendanceRegister(const AttendanceRegister&) = delete;
    AttendanceRegister& operator=(const AttendanceRegister&) = delete;

    // Session Management
    void addSession(const AttendanceSession& session);
    const std::vector<AttendanceSession>& getSessions() const;

    // Marking Attendance and Adding Corrections
    void markPresent(const Student* student, AttendanceSession* session, 
                     const std::string& method);
    
    void markPresentViaCapture(AttendanceCapture& capture, const Student* student, 
                               AttendanceSession* session);

    void addCorrection(const CorrectionRecord& rec);

    // Reporting Capabilities
    double attendancePercentage(const std::vector<Student*>& students) const;
    double attendancePercentageForStudent(const Student* student) const;
    Report eligibilityReport(double threshold) const;

    // Getters
    const std::vector<AttendanceRecord*>& getRecords() const;
};

#endif // ATTENDANCEREGISTER_H