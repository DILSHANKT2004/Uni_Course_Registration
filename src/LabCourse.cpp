#include "LabCourse.h"
#include <stdexcept>

LabCourse::LabCourse(std::string code, std::string title, int creditValue, int capacity, int labGroupSize)
    : Course(code, title, creditValue, capacity), labGroupSize(labGroupSize) {
    if (labGroupSize <= 0) {
        throw std::invalid_argument("Lab group size must be positive.");
    }
}

double LabCourse::computeGrade(double score) const {
    return score * 0.3;
}

std::string LabCourse::getType() const {
    return "Lab";
}