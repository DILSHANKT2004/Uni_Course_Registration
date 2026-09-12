#include "RotatingCodeCapture.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor initializes random seed and code duration
RotatingCodeCapture::RotatingCodeCapture(int validityDurationSeconds)
    : currentCode(""), expiry(0), validityDurationSeconds(validityDurationSeconds) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Generates a random alphanumeric string
std::string RotatingCodeCapture::generateRandomCode(size_t length) {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t max_index = sizeof(charset) - 1;
    std::string code = "";
    
    for (size_t i = 0; i < length; ++i) {
        code += charset[std::rand() % max_index];
    }
    return code;
}

// Starts the capture session by generating the first code
void RotatingCodeCapture::beginSession() {
    currentCode = generateRandomCode();
    expiry = std::time(nullptr) + validityDurationSeconds;
    std::cout << "[RotatingCodeCapture] Session started. Current Code: " 
              << currentCode << std::endl;
}

// Returns current active capture method status/token string
std::string RotatingCodeCapture::captureNext() {
    if (isExpired()) {
        // Automatically regenerate code if expired during active session
        currentCode = generateRandomCode();
        expiry = std::time(nullptr) + validityDurationSeconds;
    }
    return "RotatingCode:" + getCurrentCode();
}

// Clears session details
void RotatingCodeCapture::endSession() {
    currentCode = "";
    expiry = 0;
    std::cout << "[RotatingCodeCapture] Session ended." << std::endl;
}

// Returns the active code, regenerating it if expired
std::string RotatingCodeCapture::getCurrentCode() {
    if (isExpired()) {
        currentCode = generateRandomCode();
        expiry = std::time(nullptr) + validityDurationSeconds;
    }
    return currentCode;
}

// Validates student code submission
bool RotatingCodeCapture::validateCode(const std::string& inputCode) {
    if (isExpired()) {
        return false;
    }
    return (inputCode == currentCode);
}

// Checks if the current code has expired
bool RotatingCodeCapture::isExpired() const {
    return std::time(nullptr) >= expiry;
}