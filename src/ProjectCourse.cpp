#include "ProjectCourse.h"

ProjectCourse::ProjectCourse(std::string code, std::string title, int creditValue, int capacity, bool groupBased)
    : Course(code, title, creditValue, capacity), groupBased(groupBased) {}

// Project grading behavior: e.g., flat baseline addition for project deliverables
double ProjectCourse::computeGrade(double score) const {
    double finalScore = score*0.2;
    return  finalScore;
}

std::string ProjectCourse::getType() const {
    return "Project";
}