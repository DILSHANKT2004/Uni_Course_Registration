#ifndef ROTATINGCODECAPTURE_H
#define ROTATINGCODECAPTURE_H

#include "AttendanceCapture.h"
#include <random>
#include <string>
#include <ctime>

class RotatingCodeCapture : public AttendanceCapture {
private:
    std::string currentCode;
    std::time_t expiry;
    int validityDurationSeconds;
   
    std::string generateRandomCode(size_t length = 6);

public:
    RotatingCodeCapture(int validityDurationSeconds = 30);
    ~RotatingCodeCapture() override = default;

    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;

    std::string getCurrentCode();
    bool validateCode(const std::string& inputCode);
    bool isExpired() const;
};

#endif