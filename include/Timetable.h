#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <vector>
#include <iostream>
#include "Timeslot.h" // Required because Timetable has a composition relationship with TimeSlot

class Timetable {
private:
    std::vector<TimeSlot> slots;

public:
    // Default constructor
    Timetable() = default;

    // Adds a new time slot to the timetable
    void addSlot(const TimeSlot& slot);

    // Compares this timetable with another to detect scheduling conflicts
    bool hasClashWith(const Timetable& other) const;

    // Overloaded stream insertion operator for printing the timetable (FR6.2)
    friend std::ostream& operator<<(std::ostream& os, const Timetable& t);
};

#endif // TIMETABLE_H