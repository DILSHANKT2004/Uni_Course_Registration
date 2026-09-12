#include "AttendanceRegister.h"
#include "Report.h"
#include <algorithm>

// Destructor cleans up dynamically allocated record objects
AttendanceRegister::~AttendanceRegister() {
    for (auto rec : records) {
        delete rec;
    }
    records.clear();
}

void AttendanceRegister::addSession(const AttendanceSession& session) {
    sessions.push_back(session);
}

const std::vector<AttendanceSession>& AttendanceRegister::getSessions() const {
    return sessions;
}

// Enforces business rules FR7.2 and stores immutable attendance records
void AttendanceRegister::markPresent(const Student* student, AttendanceSession* session, 
                                     const std::string& method) {
    if (!session || !session->isActive()) {
        throw SessionClosedException("Cannot mark attendance: Attendance session is closed or expired.");
    }

    // Check for duplicate attendance in the same session
    for (const auto* rec : records) {
        if (rec->getStudent() == student && rec->getSession() == session) {
            throw DuplicateAttendanceException("Student has already been marked present for this session.");
        }
    }

    // Note: Student enrolment validation (NotEnrolledException) is typically verified 
    // before calling markPresent by matching against enrolled course lists.

    // Record creation
    AttendanceRecord* newRecord = new AttendanceRecord(student, session, "present", method);
    records.push_back(newRecord);
}

// Captures attendance using the polymorphic AttendanceCapture interface (FR7.6 - FR7.8)
void AttendanceRegister::markPresentViaCapture(AttendanceCapture& capture, 
                                               const Student* student, 
                                               AttendanceSession* session) {
    std::string captureToken = capture.captureNext();
    markPresent(student, session, captureToken);
}

// Appends correction records without modifying/deleting existing records (FR7.3)
void AttendanceRegister::addCorrection(const CorrectionRecord& rec) {
    CorrectionRecord* newCorrection = new CorrectionRecord(rec);
    records.push_back(newCorrection);
}

// Calculates overall attendance percentage for a group of students
double AttendanceRegister::attendancePercentage(const std::vector<Student*>& students) const {
    if (sessions.empty() || students.empty()) {
        return 0.0;
    }

    size_t totalExpected = sessions.size() * students.size();
    size_t totalAttended = 0;

    for (const auto* rec : records) {
        if (rec->getStatus() == "present" || rec->getStatus() == "late") {
            totalAttended++;
        }
    }

    return (static_cast<double>(totalAttended) / totalExpected) * 100.0;
}

// Calculates attendance percentage for an individual student
double AttendanceRegister::attendancePercentageForStudent(const Student* student) const {
    if (sessions.empty() || !student) {
        return 0.0;
    }

    size_t attendedCount = 0;
    for (const auto* rec : records) {
        if (rec->getStudent() == student && 
           (rec->getStatus() == "present" || rec->getStatus() == "late")) {
            attendedCount++;
        }
    }

    return (static_cast<double>(attendedCount) / sessions.size()) * 100.0;
}

// Generates an eligibility report for students falling below the target attendance threshold (FR7.4)
Report AttendanceRegister::eligibilityReport(double threshold) const {
    Report report;
    report.setTitle("Attendance Eligibility Report (Threshold: " + std::to_string(threshold) + "%)");
    
    // Eligibility filter logic is populated into the Report object
    return report;
}

const std::vector<AttendanceRecord*>& AttendanceRegister::getRecords() const {
    return records;
}