#include "TimeSlot.h"
#include <iomanip>

// Constructor
TimeSlot::TimeSlot(DayOfWeek day, Time startTime, Time endTime, std::string location)
    : day(day), startTime(startTime), endTime(endTime), location(std::move(location)) {}

// Getters
DayOfWeek TimeSlot::getDay() const {
    return day;
}

Time TimeSlot::getStartTime() const {
    return startTime;
}

Time TimeSlot::getEndTime() const {
    return endTime;
}

std::string TimeSlot::getLocation() const {
    return location;
}

// Setters
void TimeSlot::setDay(DayOfWeek d) {
    day = d;
}

void TimeSlot::setStartTime(Time start) {
    startTime = start;
}

void TimeSlot::setEndTime(Time end) {
    endTime = end;
}

void TimeSlot::setLocation(const std::string& loc) {
    location = loc;
}

// Exact equality check
bool TimeSlot::operator==(const TimeSlot& other) const {
    return (day == other.day &&
            startTime == other.startTime &&
            endTime == other.endTime &&
            location == other.location);
}

// Checks if two time slots overlap on the same day
bool TimeSlot::overlaps(const TimeSlot& other) const {
    // If they are on different days, they cannot overlap
    if (day != other.day) {
        return false;
    }

    // Overlap condition: max(start1, start2) < min(end1, end2)
    // Two slots overlap if one starts strictly before the other ends, and vice versa
    bool startsBeforeOtherEnds = startTime < other.endTime;
    bool otherStartsBeforeThisEnds = other.startTime < endTime;

    return (startsBeforeOtherEnds && otherStartsBeforeThisEnds);
}

// Helper function to convert DayOfWeek enum to string for printing
static std::string dayToString(DayOfWeek day) {
    switch (day) {
        case DayOfWeek::Monday:    return "Monday";
        case DayOfWeek::Tuesday:   return "Tuesday";
        case DayOfWeek::Wednesday: return "Wednesday";
        case DayOfWeek::Thursday:  return "Thursday";
        case DayOfWeek::Friday:    return "Friday";
        case DayOfWeek::Saturday:  return "Saturday";
        case DayOfWeek::Sunday:    return "Sunday";
        default:                   return "Unknown";
    }
}

// Stream insertion operator overload for printing
std::ostream& operator<<(std::ostream& os, const TimeSlot& t) {
    os << dayToString(t.day) << " "
       << std::setw(2) << std::setfill('0') << t.startTime.hours << ":"
       << std::setw(2) << std::setfill('0') << t.startTime.minutes << " - "
       << std::setw(2) << std::setfill('0') << t.endTime.hours << ":"
       << std::setw(2) << std::setfill('0') << t.endTime.minutes
       << " @ " << t.location;
    return os;
}