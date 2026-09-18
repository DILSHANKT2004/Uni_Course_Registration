#include "ProjectCourse.h"

ProjectCourse::ProjectCourse(std::string code, std::string title, int creditValue, int capacity, bool groupBased)
    : Course(code, title, creditValue, capacity), groupBased(groupBased) {}

double ProjectCourse::computeGrade(double score) const {
    return score * 0.2;
}

std::string ProjectCourse::getType() const {
    return "Project";
}

bool ProjectCourse::isGroupBased() const {
    return groupBased;
}