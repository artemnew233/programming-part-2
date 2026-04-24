#include "Citizen.h"

Citizen::Citizen()
    : id(0), fullName("Unknown"), age(0), districtId(0) {}

Citizen::Citizen(int id, const char* fullName, int age, int districtId)
    : id(id), fullName(fullName),
      age(age > 0 ? age : 0),
      districtId(districtId) {}

int         Citizen::getId()         const { return id; }
const char* Citizen::getFullName()   const { return fullName; }
int         Citizen::getAge()        const { return age; }
int         Citizen::getDistrictId() const { return districtId; }

void Citizen::setDistrictId(int newDistrictId) {
    districtId = newDistrictId;
}

bool Citizen::isAdult() const {
    return age >= 18;
}
