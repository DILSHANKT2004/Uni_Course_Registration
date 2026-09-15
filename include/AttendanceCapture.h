#ifndef ATTENDANCECAPTURE_H
#define ATTENDANCECAPTURE_H

#include <string>
#include <ctime>

// Abstract Base Class / Interface (FR7.6)
class AttendanceCapture {
public:
    virtual ~AttendanceCapture() = default;

    // Pure virtual functions forming the capture interface
    virtual void beginSession() = 0;
    virtual std::string captureNext() = 0;
    virtual void endSession() = 0;
};

#endif // ATTENDANCECAPTURE_H