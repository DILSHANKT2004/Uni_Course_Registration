#include "FileStorage.h"
#include "MenuUI.h"

#include <iostream>

int main() {
    Repository<Person> personRepository;
    Repository<Course> courseRepository;
    FileStorage storage(&personRepository, &courseRepository);
    const std::string dataPath = "data/system.csv";

    try {
        storage.load(dataPath);
    } catch (const std::exception& exception) {
        std::cerr << "Starting with empty data: " << exception.what() << '\n';
    }

    MenuUI menu(personRepository, courseRepository, storage, dataPath);
    menu.run();

    return 0;
}
