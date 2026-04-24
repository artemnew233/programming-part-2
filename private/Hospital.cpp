#include "Hospital.h"

Hospital::Hospital()
    : id(0), name("Unknown"), capacity(0), isPublic(true) {}

Hospital::Hospital(int id, const char* name, int capacity, bool isPublic)
    : id(id), name(name),
      capacity(capacity > 0 ? capacity : 0),
      isPublic(isPublic) {}

int         Hospital::getId()       const { return id; }
const char* Hospital::getName()     const { return name; }
int         Hospital::getCapacity() const { return capacity; }
bool        Hospital::getIsPublic() const { return isPublic; }

bool Hospital::isLargeHospital() const {
    return capacity > 200;
}
