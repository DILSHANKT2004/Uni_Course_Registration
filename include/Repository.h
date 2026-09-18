#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <utility>

template <typename T>
class Repository {
private:
    std::vector<T*> items;

public:
    Repository() = default;

    Repository(const Repository&) = delete;
    Repository& operator=(const Repository&) = delete;

    Repository(Repository&& other) noexcept
        : items(std::move(other.items)) {
        other.items.clear();
    }

    Repository& operator=(Repository&& other) noexcept {
        if (this != &other) {
            clear();
            items = std::move(other.items);
            other.items.clear();
        }
        return *this;
    }

    ~Repository() {
        clear();
    }

    void add(T* item) {
        if (item && std::find(items.begin(), items.end(), item) == items.end()) {
            items.push_back(item);
        }
    }

    void remove(T* item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            delete *it;
            items.erase(it);
        }
    }

    void clear() noexcept {
        for (T* item : items) {
            delete item;
        }
        items.clear();
    }

    T* findById(const std::string& id) const {
        for (T* item : items) {
            if (item && item->getId() == id) {
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