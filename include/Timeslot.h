#ifndef TIMESLOT_H
#define TIMESLOT_H
using namespace std;
#include <string>
#include <iostream>

// Enumeration for the day of the week
enum class DayOfWeek {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

// Simple struct to represent Time (e.g., hours and minutes)
struct Time {
    int hour;
    int minute;

    // Helper for time comparison
    bool operator<(const Time& other) const {
        if (hour == other.hour) return minute < other.minute;
        return hour < other.hour;
    }
};

class TimeSlot {
private:
    DayOfWeek day;
    Time startTime;
    Time endTime;
    string location;

public:
    // Constructor
    TimeSlot(DayOfWeek day, Time startTime, Time endTime, string location);

    // Named method for clash detection
    bool overlaps(const TimeSlot& other) const;

    // Overloaded equality operator for clash detection (FR4.4)
    bool operator==(const TimeSlot& other) const;

    // Overloaded stream insertion operator for printing (FR6.2)
    friend ostream& operator<<(ostream& os, const TimeSlot& t);

    // Const-correct getters
    DayOfWeek getDay() const;
    Time getStartTime() const;
    Time getEndTime() const;
    const std::string& getLocation() const;
};

#endif // TIMESLOT_H