#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Repository {
private:
    std::vector<T*> items;

public:
    ~Repository() {
        for (T* item : items) {
            delete item;
        }
        items.clear();
    }

    void add(T* item) {
        if (item) {
            items.push_back(item);
        }
    }

    void remove(T* item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        }
    }

    T* findById(const std::string& id) const {
        for (T* item : items) {
            if (item->getId() == id) {
                return item;
            }
        }
        return nullptr;
    }

    std::vector<T*> getAll() const {
        return items;
    }
};

#endif 