#include "School.h"

School::School()
    : id(0), name("Unknown"), capacity(0), level("primary") {}

School::School(int id, const char* name, int capacity, const char* level)
    : id(id), name(name),
      capacity(capacity > 0 ? capacity : 0),
      level(level) {}

int         School::getId()       const { return id; }
const char* School::getName()     const { return name; }
int         School::getCapacity() const { return capacity; }
const char* School::getLevel()    const { return level; }

bool School::isPrimary() const {
    // compare first character for simplicity (no <cstring> dependency)
    return level != nullptr && level[0] == 'p';
}
