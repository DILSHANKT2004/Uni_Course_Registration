#include "LectureCourse.h"

LectureCourse::LectureCourse(std::string code, std::string title, int creditValue, int capacity)
    : Course(code, title, creditValue, capacity) {}

// Standard grading: returns the raw score
double LectureCourse::computeGrade(double score) const {
    double finalScore = score*0.5; // No additional weighting for lecture courses
    return finalScore;
}

std::string LectureCourse::getType() const {
    return "Lecture";
}