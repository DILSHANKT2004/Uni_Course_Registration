#include "AttendanceCapture.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Constructor for RotatingCodeCapture
RotatingCodeCapture::RotatingCodeCapture(int durationSeconds)
    : currentCode(""), expiry(0), codeDurationSeconds(durationSeconds) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Generates an alphanumeric code
std::string RotatingCodeCapture::generateRandomCode(int length) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t maxIndex = sizeof(charset) - 1;
    std::string code = "";
    
    for (int i = 0; i < length; ++i) {
        code += charset[std::rand() % maxIndex];
    }
    return code;
}

// Starts a new session by generating a short random code with an expiration time
void RotatingCodeCapture::beginSession() {
    currentCode = generateRandomCode(6);
    expiry = std::time(nullptr) + codeDurationSeconds;
}

// Returns the capture method metadata tag used when registering attendance
std::string RotatingCodeCapture::captureNext() {
    return "RotatingCode:" + currentCode;
}

// Terminates the session and invalidates the active code
void RotatingCodeCapture::endSession() {
    currentCode = "";
    expiry = 0;
}

// Validates whether an entered code matches and is still unexpired
bool RotatingCodeCapture::validateCode(const std::string& inputCode) const {
    if (currentCode.empty()) {
        return false;
    }

    std::time_t now = std::time(nullptr);
    if (now > expiry) {
        return false;
    }

    return (inputCode == currentCode);
}

std::string RotatingCodeCapture::getCurrentCode() const {
    return currentCode;
}