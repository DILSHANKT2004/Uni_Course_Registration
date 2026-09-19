#include "AttendanceRegister.h"
#include "Student.h"
#include "Report.h"
#include <algorithm>
#include <set>

AttendanceRegister::AttendanceRegister() {
    sessions.reserve(100);
}

// Destructor cleans up dynamically allocated record objects
AttendanceRegister::~AttendanceRegister() {
    for (auto rec : records) {
        delete rec;
    }
    records.clear();
}

void AttendanceRegister::addSession(const AttendanceSession& session) {
    auto it = std::find_if(sessions.begin(), sessions.end(),
        [&](const AttendanceSession& existing) {
            return existing.getSessionId() == session.getSessionId();
        });

    if (it == sessions.end()) {
        sessions.push_back(session);
    }
}

const std::vector<AttendanceSession>& AttendanceRegister::getSessions() const {
    return sessions;
}

AttendanceSession* AttendanceRegister::findSession(const std::string& sessionId) {
    for (AttendanceSession& session : sessions) {
        if (session.getSessionId() == sessionId) {
            return &session;
        }
    }
    return nullptr;
}

// Enforces business rules FR7.2 and stores immutable attendance records
void AttendanceRegister::markPresent(const Student* student, AttendanceSession* session,
                                     const std::string& method) {
    if (!student) {
        throw std::invalid_argument("Cannot mark attendance: student pointer is null.");
    }
    if (!session) {
        throw std::invalid_argument("Cannot mark attendance: session pointer is null.");
    }
    if (!session->isActive()) {
        throw SessionClosedException("Cannot mark attendance: Attendance session is closed or expired.");
    }

    for (const auto* rec : records) {
        if (rec->getStudent() == student && rec->getSession() == session) {
            throw DuplicateAttendanceException("Student has already been marked present for this session.");
        }
    }

    AttendanceRecord* newRecord = new AttendanceRecord(student, session, "present", method);
    records.push_back(newRecord);
}

// Captures attendance using the polymorphic AttendanceCapture interface (FR7.6 - FR7.8)
void AttendanceRegister::markPresentViaCapture(AttendanceCapture& capture,
                                               const Student* student,
                                               AttendanceSession* session) {
    std::string captureToken = capture.captureNext();
    if (captureToken.empty()) {
        throw AttendanceException("Cannot mark attendance: captured token is empty.");
    }

    markPresent(student, session, captureToken);
}

void AttendanceRegister::restoreRecord(const Student* student, AttendanceSession* session,
                                       const std::string& status, const std::string& method,
                                       std::time_t timestamp) {
    if (student && session) {
        records.push_back(new AttendanceRecord(student, session, status, method, timestamp));
    }
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
        if (std::find(students.begin(), students.end(), rec->getStudent()) != students.end() &&
            (rec->getStatus() == "present" || rec->getStatus() == "late")) {
            totalAttended++;
        }
    }

    if (totalExpected == 0) {
        return 0.0;
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
    Report report("Attendance Eligibility Report (Threshold: " + std::to_string(threshold) + "%)");

    if (sessions.empty()) {
        report.addLine("No sessions have been recorded yet.");
        return report;
    }

    std::vector<const Student*> students;
    for (const auto* rec : records) {
        if (!rec || !rec->getStudent()) {
            continue;
        }

        if (std::find(students.begin(), students.end(), rec->getStudent()) == students.end()) {
            students.push_back(rec->getStudent());
        }
    }

    if (students.empty()) {
        report.addLine("No attendance records available.");
        return report;
    }

    bool foundEligibleStudent = false;
    for (const Student* student : students) {
        const double percentage = attendancePercentageForStudent(student);
        if (percentage < threshold) {
            foundEligibleStudent = true;
            report.addLine(student->getName() + " (" + student->getId() + "): " +
                           std::to_string(percentage) + "%");
        }
    }

    if (!foundEligibleStudent) {
        report.addLine("No students are below the attendance threshold.");
    }

    return report;
}

const std::vector<AttendanceRecord*>& AttendanceRegister::getRecords() const {
    return records;
}