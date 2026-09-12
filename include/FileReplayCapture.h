#ifndef FILEREPLAYCAPTURE_H
#define FILEREPLAYCAPTURE_H

#include "AttendanceCapture.h"
#include <fstream>
#include <string>

class FileReplayCapture : public AttendanceCapture {
private:
    std::string filePath;
    std::ifstream inputFile;

public:
    // Constructors & Destructor
    explicit FileReplayCapture(std::string filePath = "attendance_input.txt");
    ~FileReplayCapture() override;

    // Pure virtual implementations from AttendanceCapture interface
    void beginSession() override;
    std::string captureNext() override;
    void endSession() override;

    // Helper methods
    void setFilePath(const std::string& path);
    bool hasMoreEvents() const;
};

#endif // FILEREPLAYCAPTURE_H