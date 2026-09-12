#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "Timeslot.h"
#include <vector>
#include <iostream>

class Timetable {
private:
    std::vector<TimeSlot> slots; // Composition: Timetable owns its TimeSlots

public:
    // Default Constructor
    Timetable() = default;

    // Adds a time slot to the timetable
    void addSlot(const TimeSlot& slot);

    // Getter for time slots
    const std::vector<TimeSlot>& getSlots() const;

    // Checks if adding 'other' timetable creates a time clash with existing slots
    bool hasClashWith(const Timetable& other) const;

    // Stream insertion operator overload for output
    friend std::ostream& operator<<(std::ostream& os, const Timetable& t);
};

#endif // TIMETABLE_H