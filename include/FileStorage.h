#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "Storage.h"
#include "Repository.h"
#include "Person.h"
#include "Course.h"
#include <string>

class FileStorage : public Storage {
private:
    Repository<Person>* personRepo;
    Repository<Course>* courseRepo;

public:
    FileStorage(Repository<Person>* pRepo, Repository<Course>* cRepo);
    
    ~FileStorage() override = default;

    void load(const std::string& path) override;
    void save(const std::string& path) override;
};

#endif 