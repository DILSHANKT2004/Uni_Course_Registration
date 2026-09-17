#ifndef STORAGE_H
#define STORAGE_H

#include <string>

class Storage {
public:
    virtual ~Storage() = default;
    virtual void load(const std::string& path) = 0;
    virtual void save(const std::string& path) = 0;
};

#endif 