#ifndef ATTENDANCESESSION_H
#define ATTENDANCESESSION_H

#include "TimeSlot.h"
#include <string>
#include <ctime>

class AttendanceSession {
private:
    std::string sessionId;
    TimeSlot slot;
    std::time_t openTime;
    int expiryDuration; // Duration in minutes
    bool isOpen;

public:
    // Constructors
    AttendanceSession();
    AttendanceSession(std::string sessionId, TimeSlot slot, int expiryDurationMinutes);

    // Core functionality
    void open();
    void close();
    bool isActive() const;

    // Getters
    std::string getSessionId() const;
    TimeSlot getSlot() const;
    std::time_t getOpenTime() const;
    int getExpiryDuration() const;
};

#endif // ATTENDANCESESSION_H