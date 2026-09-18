#include "LectureCourse.h"

LectureCourse::LectureCourse(std::string code, std::string title, int creditValue, int capacity)
    : Course(code, title, creditValue, capacity) {}

double LectureCourse::computeGrade(double score) const {
    return score * 0.5;
}

std::string LectureCourse::getType() const {
    return "Lecture";
}