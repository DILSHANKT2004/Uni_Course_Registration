#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <iostream>
#include <string>

enum class DayOfWeek {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

struct Time {
    int hours;
    int minutes;

    bool operator<(const Time& other) const {
        if (hours != other.hours) {
            return hours < other.hours;
        }
        return minutes < other.minutes;
    }

    bool operator<=(const Time& other) const {
        return *this < other ||
               (hours == other.hours && minutes == other.minutes);
    }

    bool operator==(const Time& other) const {
        return hours == other.hours &&
               minutes == other.minutes;
    }
};

class TimeSlot {
private:
    DayOfWeek day;
    Time startTime;
    Time endTime;
    std::string location;

public:
    TimeSlot(
        DayOfWeek day,
        Time startTime,
        Time endTime,
        std::string location
    );

    TimeSlot() = default;

    DayOfWeek getDay() const;
    Time getStartTime() const;
    Time getEndTime() const;
    std::string getLocation() const;

    void setDay(DayOfWeek day);
    void setStartTime(Time startTime);
    void setEndTime(Time endTime);
    void setLocation(const std::string& location);

    bool operator==(const TimeSlot& other) const;
    bool overlaps(const TimeSlot& other) const;

    friend std::ostream& operator<<(
        std::ostream& os,
        const TimeSlot& timeSlot
    );
};

#endif // TIMESLOT_H