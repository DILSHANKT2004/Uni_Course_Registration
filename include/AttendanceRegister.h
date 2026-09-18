#ifndef ATTENDANCEREGISTER_H
#define ATTENDANCEREGISTER_H

#include "AttendanceRecord.h"
#include "CorrectionRecord.h"
#include "AttendanceSession.h"
#include "AttendanceCapture.h"
#include "CustomExceptions.h"
#include <vector>
#include <string>

class Student;
class Lecturer;
class Report;

class AttendanceRegister {
private:
    std::vector<AttendanceRecord*> records; 
    std::vector<AttendanceSession> sessions;

public:
    AttendanceRegister() = default;
    ~AttendanceRegister();

    AttendanceRegister(const AttendanceRegister&) = delete;
    AttendanceRegister& operator=(const AttendanceRegister&) = delete;

    void addSession(const AttendanceSession& session);
    const std::vector<AttendanceSession>& getSessions() const;

    void markPresent(const Student* student, AttendanceSession* session, 
                     const std::string& method);
    
    void markPresentViaCapture(AttendanceCapture& capture, const Student* student, 
                               AttendanceSession* session);

    void addCorrection(const CorrectionRecord& rec);

    double attendancePercentage(const std::vector<Student*>& students) const;
    double attendancePercentageForStudent(const Student* student) const;
    Report eligibilityReport(double threshold) const;

    const std::vector<AttendanceRecord*>& getRecords() const;
};

#endif 