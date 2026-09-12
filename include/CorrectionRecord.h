#ifndef CORRECTIONRECORD_H
#define CORRECTIONRECORD_H

#include "AttendanceRecord.h"
#include <string>

// Forward declaration
class Lecturer;

class CorrectionRecord : public AttendanceRecord {
private:
    const Lecturer* actingLecturer;
    std::string reason;

public:
    // Constructor
    CorrectionRecord(const Student* student, 
                     const AttendanceSession* session, 
                     std::string status, 
                     std::string captureMethod, 
                     const Lecturer* actingLecturer, 
                     std::string reason);

    // Virtual Destructor
    virtual ~CorrectionRecord() = default;

    // Getters
    const Lecturer* getActingLecturer() const;
    std::string getReason() const;
};

#endif // CORRECTIONRECORD_H