#include "FileReplayCapture.h"
#include <iostream>

// Constructor initializes file path
FileReplayCapture::FileReplayCapture(std::string filePath)
    : filePath(std::move(filePath)) {}

// Destructor ensures file streams are closed properly
FileReplayCapture::~FileReplayCapture() {
    endSession();
}

// Opens the source text file for replaying capture events
void FileReplayCapture::beginSession() {
    if (inputFile.is_open()) {
        inputFile.close();
    }

    inputFile.open(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "[FileReplayCapture] Warning: Failed to open file " << filePath << std::endl;
    } else {
        std::cout << "[FileReplayCapture] Replay session started from file: " << filePath << std::endl;
    }
}

// Reads and returns the next record token/event line from the file
std::string FileReplayCapture::captureNext() {
    if (!inputFile.is_open() || inputFile.eof()) {
        return "";
    }

    std::string line;
    if (std::getline(inputFile, line)) {
        return line;
    }

    return "";
}

// Closes the file handle
void FileReplayCapture::endSession() {
    if (inputFile.is_open()) {
        inputFile.close();
        std::cout << "[FileReplayCapture] Replay session closed." << std::endl;
    }
}

// Set custom replay file path
void FileReplayCapture::setFilePath(const std::string& path) {
    filePath = path;
}

// Checks if file stream has more remaining capture tokens
bool FileReplayCapture::hasMoreEvents() const {
    return inputFile.is_open() && !inputFile.eof();
}