#ifndef PROJECTCOURSE_H
#define PROJECTCOURSE_H

#include "Course.h"

class ProjectCourse : public Course {
private:
    bool groupBased;

public:
    ProjectCourse(std::string code, std::string title, int creditValue, int capacity, bool groupBased);

    double computeGrade(double score) const override;
    std::string getType() const;
    bool isGroupBased() const;
};

#endif 