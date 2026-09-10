#ifndef PROJECTCOURSE_H
#define PROJECTCOURSE_H

#include "Course.h"

class ProjectCourse : public Course {
private:
    bool groupBased;

public:
    // Constructor includes the groupBased flag
    ProjectCourse(std::string code, std::string title, int creditValue, int capacity, bool groupBased);

    // Overridden methods
    double computeGrade(double score) const override;
    std::string getType() const;
};

#endif // PROJECTCOURSE_H