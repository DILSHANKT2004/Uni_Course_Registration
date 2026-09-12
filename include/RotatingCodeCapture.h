#ifndef ROTATINGCODECAPTURE_H
#define ROTATINGCODECAPTURE_H

#include "AttendanceCapture.h"
#include <string>
#include <ctime>

class RotatingCodeCapture : public AttendanceCapture {
private:
    std::string currentCode;
    std::time_t expiry;
    int validityDurationSeconds;

    // Helper to generate a short random alphanumeric code
    std::string generateRandomCode(size_t length = 6);

public:
    // Constructor (default validity duration e.g., 30 seconds)
    RotatingCodeCapture(int validityDurationSeconds = 30);
    ~RotatingCodeCapture() override = default;

    // Pure virtual implementations from AttendanceCapture
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;

    // Specific methods for Option A (Rotating Code)
    std::string getCurrentCode();
    bool validateCode(const std::string& inputCode);
    bool isExpired() const;
};

#endif // ROTATINGCODECAPTURE_H