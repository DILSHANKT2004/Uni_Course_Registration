#include "Report.h"

// Constructor utilizing an initializer list
Report::Report(std::string title) : title(title) {
}

// Appends a new line of data to the internal vector
void Report::addLine(const std::string& line) {
    lines.push_back(line);
}

// Dedicated print method that reuses the overloaded operator<<
void Report::print() const {
    std::cout << *this; 
}

// Overloaded stream insertion operator for outputting the report[cite: 1]
std::ostream& operator<<(std::ostream& os, const Report& report) {
    os << "\n========================================\n";
    os << " REPORT: " << report.title << "\n";
    os << "========================================\n";
    
    if (report.lines.empty()) {
        os << "No data available in this report.\n";
    } else {
        for (const std::string& line : report.lines) {
            os << line << "\n";
        }
    }
    
    os << "========================================\n";
    return os;
}