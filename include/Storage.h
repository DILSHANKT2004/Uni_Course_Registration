#ifndef STORAGE_H
#define STORAGE_H

#include <string>

class Storage {
public:
    virtual ~Storage() = default;
    virtual void save(std::string filename) = 0; 
    virtual void load(std::string filename) = 0; 
};

#endif 