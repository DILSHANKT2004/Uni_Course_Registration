#ifndef LABCOURSE_H
#define LABCOURSE_H

#include "Course.h"

class LabCourse : public Course {
private:
    int labGroupSize;

public:
    // Constructor includes the new labGroupSize parameter
    LabCourse(std::string code, std::string title, int creditValue, int capacity, int labGroupSize);

    // Overridden methods
    double computeGrade(double score) const override;
    std::string getType() const;
};

#endif // LABCOURSE_H