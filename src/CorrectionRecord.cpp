#include "CorrectionRecord.h"

// Parametrized constructor passing base values up to AttendanceRecord
CorrectionRecord::CorrectionRecord(const Student* student, 
                                   const AttendanceSession* session, 
                                   std::string status, 
                                   std::string captureMethod, 
                                   const Lecturer* actingLecturer, 
                                   std::string reason)
    : AttendanceRecord(student, session, std::move(status), std::move(captureMethod)),
      actingLecturer(actingLecturer), 
      reason(std::move(reason)) {}

// Getter for the lecturer making the correction
const Lecturer* CorrectionRecord::getActingLecturer() const {
    return actingLecturer;
}

// Getter for the correction reason
std::string CorrectionRecord::getReason() const {
    return reason;
}