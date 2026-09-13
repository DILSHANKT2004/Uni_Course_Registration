#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Storage.h"
#include <vector>
#include <string>
#include <map>

template <typename T>
class Repository : public Storage {
private:
    std::map<std::string, T*> data;

public:
    ~Repository() {
        for (auto const& [key, val] : data) {
            delete val;
        }
    }

    std::vector<T*> getAll() { //[cite: 1]
        std::vector<T*> list;
        for (auto const& [key, val] : data) {
            list.push_back(val);
        }
        return list;
    }

    T* findById(std::string id) { //[cite: 1]
        if (data.find(id) != data.end()) {
            return data[id];
        }
        return nullptr;
    }

    void add(std::string id, T* item) {
        data[id] = item;
    }

    
    void save(std::string filename) override {
        
    }

    void load(std::string filename) override {

    }
};

#endif 