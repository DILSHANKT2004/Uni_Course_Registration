#include "LabCourse.h"

LabCourse::LabCourse(std::string code, std::string title, int creditValue, int capacity, int labGroupSize)
    : Course(code, title, creditValue, capacity), labGroupSize(labGroupSize) {}

// Lab grading behavior: e.g., includes a standard 5% bonus for practical completion
double LabCourse::computeGrade(double score) const {
    double finalScore = score * 0.3;//30% weight for lab component
    return finalScore ;
}

std::string LabCourse::getType() const {
    return "Lab";
}