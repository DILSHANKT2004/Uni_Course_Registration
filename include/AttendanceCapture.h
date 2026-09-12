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

// Concrete implementation using Rotating Session Codes (Option A - FR7.7 & FR7.8)
class RotatingCodeCapture : public AttendanceCapture {
private:
    std::string currentCode;
    std::time_t expiry;
    int codeDurationSeconds;

    std::string generateRandomCode(int length = 6);

public:
    explicit RotatingCodeCapture(int durationSeconds = 300);
    ~RotatingCodeCapture() override = default;

    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;

    // Specific methods for Option A verification
    bool validateCode(const std::string& inputCode) const;
    std::string getCurrentCode() const;
};

#endif // ATTENDANCECAPTURE_H