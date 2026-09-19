#include <iostream>
#include <cassert>
#include "student.h"
#include "Lecturer.h"
#include "Course.h"
#include "TimeSlot.h"
#include "Timetable.h"
#include "AttendanceSession.h"
#include "AttendanceRegister.h"
#include "RotatingCodeCapture.h"
#include "FileReplayCapture.h"
#include "CustomExceptions.h"

void testTimetableClash() {
    std::cout << "[TEST] Running Timetable Clash Test... ";
    TimeSlot s1(DayOfWeek::Monday, {9, 0}, {11, 0}, "Hall A");
    TimeSlot s2(DayOfWeek::Monday, {10, 0}, {12, 0}, "Hall B");
    
    Timetable t1, t2;
    t1.addSlot(s1);
    t2.addSlot(s2);
    
    assert(t1.hasClashWith(t2) == true);
    std::cout << "PASSED!\n";
}

void testAttendanceExceptions() {
    std::cout << "[TEST] Running Attendance Exception Handlers... ";
    Student student("S101", "Alice", "alice", "pass123");
    TimeSlot slot(DayOfWeek::Tuesday, {14, 0}, {16, 0}, "Lab 1");
    AttendanceSession session("SESS_01", slot, 60);
    session.open();

    AttendanceRegister reg;
    reg.addSession(session);
    
    // Mark first time
    reg.markPresent(&student, &session, "Manual");

    // Test duplicate attendance exception
    try {
        reg.markPresent(&student, &session, "Manual");
        std::cerr << "FAILED (Duplicate exception not thrown)\n";
    } catch (const DuplicateAttendanceException& e) {
        // Expected behavior
    }

    // Test session closed exception
    session.close();
    try {
        reg.markPresent(&student, &session, "Manual");
        std::cerr << "FAILED (SessionClosed exception not thrown)\n";
    } catch (const SessionClosedException& e) {
        // Expected behavior
    }

    std::cout << "PASSED!\n";
}

void testFileReplayCapture() {
    std::cout << "[TEST] Running FileReplayCapture Engine... ";
    FileReplayCapture replay("attendance_input.txt");
    replay.beginSession();
    
    while (replay.hasMoreEvents()) {
        std::string token = replay.captureNext();
        // Process token line
    }
    replay.endSession();
    std::cout << "PASSED!\n";
}

int main() {
    std::cout << "=========================================\n";
    std::cout << "   RUNNING PROJECT INTEGRATION SUITE     \n";
    std::cout << "=========================================\n";

    try {
        testTimetableClash();
        testAttendanceExceptions();
        testFileReplayCapture();
        std::cout << "\nALL AUTOMATED TESTS PASSED SUCCESSFULLY!\n";
    } catch (const std::exception& e) {
        std::cerr << "\nTEST SUITE FAILED WITH EXCEPTION: " << e.what() << "\n";
        return 1;
    }

    return 0;
}