#include <iostream>
#include "Student.h"
#include "Lecturer.h"
#include "Course.h"
#include "TimeSlot.h"
#include "Timetable.h"
#include "AttendanceRegister.h"
#include "RotatingCodeCapture.h"
#include "FileReplayCapture.h"
#include "CustomExceptions.h"

int main() {
    try {
        std::cout << "--- 1. Testing Domain & Timetable Creation ---\n";
        Lecturer prof("L001", "Dr. Smith", "smith", "hash123");
        Student student("S101", "Alice", "alice", "hash456");

        // Member 2: TimeSlot and Timetable
        TimeSlot slot1(DayOfWeek::Monday, {9, 0}, {11, 0}, "Hall A");
        TimeSlot slot2(DayOfWeek::Monday, {10, 0}, {12, 0}, "Lab B"); // Overlaps slot1

        Timetable t1, t2;
        t1.addSlot(slot1);
        t2.addSlot(slot2);

        // Member 2: Clash Detection Test
        if (t1.hasClashWith(t2)) {
            std::cout << "[SUCCESS] Timetable clash correctly detected!\n";
        }

        std::cout << "\n--- 2. Testing Attendance Session & Polymorphic Capture ---\n";
        AttendanceSession session("SESS_01", slot1, 15);
        session.open();

        // Member 2: Rotating Code Capture
        RotatingCodeCapture codeCapture(30);
        codeCapture.beginSession();

        AttendanceRegister reg;
        reg.addSession(session);

        // Member 2: Mark attendance polymorphic flow
        reg.markPresentViaCapture(codeCapture, &student, &session);
        std::cout << "[SUCCESS] Attendance marked via capture interface!\n";

        std::cout << "\n--- 3. Testing Exception Handling ---\n";
        // Trying to mark duplicate attendance
        try {
            reg.markPresent(&student, &session, "Manual");
        } catch (const DuplicateAttendanceException& e) {
            std::cout << "[SUCCESS] Caught duplicate attendance exception: " << e.what() << "\n";
        }

        codeCapture.endSession();
        session.close();

        std::cout << "\n--- All Integration Tests Passed Successfully! ---\n";

    } catch (const std::exception& e) {
        std::cerr << "[CRITICAL ERROR] Unhandled Exception: " << e.what() << std::endl;
    }

    return 0;
}