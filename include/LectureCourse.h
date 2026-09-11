#ifndef LECTURECOURSE_H
#define LECTURECOURSE_H

#include "Course.h"

class LectureCourse : public Course {
public:
    // Constructor passes parameters up to the base class
    LectureCourse(std::string code, std::string title, int creditValue, int capacity);

    // Overridden methods
    double computeGrade(double score) const override;
    std::string getType() const;
};

#endif // LECTURECOURSE_H