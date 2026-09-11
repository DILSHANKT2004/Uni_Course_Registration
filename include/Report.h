#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include <iostream>

class Report {
private:
    std::string title;
    std::vector<std::string> lines;

public:
    // Constructor
    Report(std::string title);

    // Method to append a new line of text to the report
    void addLine(const std::string& line);

    // Dedicated print method
    void print() const;

    // Overloaded stream insertion operator for formatting output[cite: 1]
    friend std::ostream& operator<<(std::ostream& os, const Report& report);
};

#endif // REPORT_H