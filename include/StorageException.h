#ifndef STORAGE_EXCEPTION_H
#define STORAGE_EXCEPTION_H

#include <exception>
#include <string>

class StorageException : public std::exception {
private:
    std::string message;

public:
    explicit StorageException(const std::string& msg) : message("Storage Error: " + msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif 