#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>
#include <iostream>

// Enumeration for Days of the Week as shown in the UML diagram
enum class DayOfWeek {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

// Represents a specific time duration (HH:MM)
struct Time {
    int hours;
    int minutes;

    bool operator<(const Time& other) const {
        if (hours != other.hours) return hours < other.hours;
        return minutes < other.minutes;
    }

    bool operator<=(const Time& other) const {
        return *this < other || (hours == other.hours && minutes == other.minutes);
    }

    bool operator==(const Time& other) const {
        return hours == other.hours && minutes == other.minutes;
    }
};

class TimeSlot {
private:
    DayOfWeek day;
    Time startTime;
    Time endTime;
    std::string location;

public:
    // Constructor
    TimeSlot(DayOfWeek day, Time startTime, Time endTime, std::string location);

    // Default Constructor
    TimeSlot() = default;

    // Getters (const-correct)
    DayOfWeek getDay() const;
    Time getStartTime() const;
    Time getEndTime() const;
    std::string getLocation() const;

    // Setters
    void setDay(DayOfWeek d);
    void setStartTime(Time start);
    void setEndTime(Time end);
    void setLocation(const std::string& loc);

    // Operator Overloading for equality and clash detection
    bool operator==(const TimeSlot& other) const;
    bool overlaps(const TimeSlot& other) const;

    // Stream Insertion Operator Overloading for displaying TimeSlot info
    friend std::ostream& operator<<(std::ostream& os, const TimeSlot& t);
};

#endif // TIMESLOT_H