#include "FileReplayCapture.h"
#include <string>

FileReplayCapture::FileReplayCapture(const std::string& filename) {
    fileStream.open(filename);
}

FileReplayCapture::~FileReplayCapture() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

void FileReplayCapture::captureNext() { //
    if (!fileStream.is_open() || fileStream.eof()) {
        return;
    }
    std::string studentId;
    std::getline(fileStream, studentId);
    
    
    
}