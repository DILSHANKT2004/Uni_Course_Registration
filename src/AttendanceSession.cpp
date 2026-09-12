#include "AttendanceSession.h"

// Default constructor
AttendanceSession::AttendanceSession() 
    : sessionId(""), slot(), openTime(0), expiryDuration(10), isOpen(false) {}

// Parameterized constructor
AttendanceSession::AttendanceSession(std::string sessionId, TimeSlot slot, int expiryDurationMinutes)
    : sessionId(std::move(sessionId)), slot(slot), openTime(0), expiryDuration(expiryDurationMinutes), isOpen(false) {}

// Opens the attendance session and records the timestamp
void AttendanceSession::open() {
    openTime = std::time(nullptr);
    isOpen = true;
}

// Manually closes the session
void AttendanceSession::close() {
    isOpen = false;
}

// Checks if the session is currently active (is open and not expired)
bool AttendanceSession::isActive() const {
    if (!isOpen) {
        return false;
    }

    // Check against current time for automatic expiration
    std::time_t currentTime = std::time(nullptr);
    double elapsedSeconds = std::difftime(currentTime, openTime);
    double maxDurationSeconds = expiryDuration * 60.0;

    return elapsedSeconds < maxDurationSeconds;
}

// Getters
std::string AttendanceSession::getSessionId() const {
    return sessionId;
}

TimeSlot AttendanceSession::getSlot() const {
    return slot;
}

std::time_t AttendanceSession::getOpenTime() const {
    return openTime;
}

int AttendanceSession::getExpiryDuration() const {
    return expiryDuration;
}