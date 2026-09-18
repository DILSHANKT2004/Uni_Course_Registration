#include "Timetable.h"
#include <algorithm>

// Add a slot to the timetable
void Timetable::addSlot(const TimeSlot& slot) {
    slots.push_back(slot);
}

void Timetable::removeSlot(const TimeSlot& slot) {
    slots.erase(std::remove(slots.begin(), slots.end(), slot), slots.end());
}

// Get access to all time slots (const reference)
const std::vector<TimeSlot>& Timetable::getSlots() const {
    return slots;
}

// Check for clashes between this timetable and another timetable
bool Timetable::hasClashWith(const Timetable& other) const {
    for (const auto& mySlot : slots) {
        for (const auto& otherSlot : other.getSlots()) {
            // Utilizes the TimeSlot::overlaps method for clash detection
            if (mySlot.overlaps(otherSlot)) {
                return true; // Clash detected
            }
        }
    }
    return false; // No clashes found
}

// Stream insertion operator to print the entire timetable
std::ostream& operator<<(std::ostream& os, const Timetable& t) {
    if (t.slots.empty()) {
        os << "  [No scheduled slots]";
        return os;
    }

    for (size_t i = 0; i < t.slots.size(); ++i) {
        os << "  - " << t.slots[i];
        if (i != t.slots.size() - 1) {
            os << "\n";
        }
    }
    return os;
}