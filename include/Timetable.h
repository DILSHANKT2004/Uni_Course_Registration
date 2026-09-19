#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "Timeslot.h"
#include <vector>
#include <iostream>

class Timetable {
private:
    std::vector<TimeSlot> slots; 
public:
    Timetable() = default;

    void addSlot(const TimeSlot& slot);

    void updateSlot(std::size_t index, const TimeSlot& slot);

    void removeSlot(const TimeSlot& slot);

    const std::vector<TimeSlot>& getSlots() const;

    bool hasClashWith(const Timetable& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Timetable& t);
};

#endif 