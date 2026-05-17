#include "City.h"

City::City()
    : name("Unknown"), population(0),
      districtCount(0), hospitalCount(0), schoolCount(0) {
    for (int i = 0; i < MAX_DISTRICTS; ++i) districts[i] = nullptr;
    for (int i = 0; i < MAX_HOSPITALS; ++i) hospitals[i] = nullptr;
    for (int i = 0; i < MAX_SCHOOLS;   ++i) schools[i]   = nullptr;
}

City::City(const char* name, int population)
    : name(name),
      population(population >= 0 ? population : 0),
      districtCount(0), hospitalCount(0), schoolCount(0) {
    for (int i = 0; i < MAX_DISTRICTS; ++i) districts[i] = nullptr;
    for (int i = 0; i < MAX_HOSPITALS; ++i) hospitals[i] = nullptr;
    for (int i = 0; i < MAX_SCHOOLS;   ++i) schools[i]   = nullptr;
}

const char* City::getName()          const { return name; }
int         City::getPopulation()    const { return population; }
int         City::getDistrictCount() const { return districtCount; }
int         City::getHospitalCount() const { return hospitalCount; }
int         City::getSchoolCount()   const { return schoolCount; }

const District* City::getDistrictAt(int index) const {
    if (index < 0 || index >= districtCount) return nullptr;
    return districts[index];
}
const Hospital* City::getHospitalAt(int index) const {
    if (index < 0 || index >= hospitalCount) return nullptr;
    return hospitals[index];
}
const School* City::getSchoolAt(int index) const {
    if (index < 0 || index >= schoolCount) return nullptr;
    return schools[index];
}

bool City::hasDistrict(int districtId) const {
    for (int i = 0; i < districtCount; ++i) {
        if (districts[i] != nullptr && districts[i]->getId() == districtId) {
            return true;
        }
    }
    return false;
}
bool City::hasHospital(int hospitalId) const {
    for (int i = 0; i < hospitalCount; ++i) {
        if (hospitals[i] != nullptr && hospitals[i]->getId() == hospitalId) {
            return true;
        }
    }
    return false;
}
bool City::hasSchool(int schoolId) const {
    for (int i = 0; i < schoolCount; ++i) {
        if (schools[i] != nullptr && schools[i]->getId() == schoolId) {
            return true;
        }
    }
    return false;
}

bool City::addDistrict(District& district) {
    if (districtCount >= MAX_DISTRICTS || hasDistrict(district.getId())) {
        return false;
    }
    districts[districtCount] = &district;
    ++districtCount;
    return true;
}
bool City::addHospital(Hospital& hospital) {
    if (hospitalCount >= MAX_HOSPITALS || hasHospital(hospital.getId())) {
        return false;
    }
    hospitals[hospitalCount] = &hospital;
    ++hospitalCount;
    return true;
}
bool City::addSchool(School& school) {
    if (schoolCount >= MAX_SCHOOLS || hasSchool(school.getId())) {
        return false;
    }
    schools[schoolCount] = &school;
    ++schoolCount;
    return true;
}

int City::totalPublicHospitals() const {
    int count = 0;
    for (int i = 0; i < hospitalCount; ++i) {
        if (hospitals[i] != nullptr && hospitals[i]->getIsPublic()) {
            ++count;
        }
    }
    return count;
}
