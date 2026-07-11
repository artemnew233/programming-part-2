#include "District.h"

District::District()
    : id(0), name("Unknown"), areaSqKm(1.0), citizenCount(0) {
    for (int i = 0; i < MAX_CITIZENS; ++i) {
        citizens[i] = nullptr;
    }
}

District::District(int id, const char* name, double areaSqKm)
    : id(id), name(name),
      areaSqKm(areaSqKm > 0.0 ? areaSqKm : 1.0),
      citizenCount(0) {
    for (int i = 0; i < MAX_CITIZENS; ++i) {
        citizens[i] = nullptr;
    }
}

int         District::getId()           const { return id; }
const char* District::getName()         const { return name; }
double      District::getAreaSqKm()     const { return areaSqKm; }
int         District::getCitizenCount() const { return citizenCount; }

const Citizen* District::getCitizenAt(int index) const {
    if (index < 0 || index >= citizenCount) {
        return nullptr;
    }
    return citizens[index];
}

bool District::containsCitizen(int citizenId) const {
    for (int i = 0; i < citizenCount; ++i) {
        if (citizens[i] != nullptr && citizens[i]->getId() == citizenId) {
            return true;
        }
    }
    return false;
}

bool District::addCitizen(Citizen& citizen) {
    if (citizenCount >= MAX_CITIZENS || containsCitizen(citizen.getId())) {
        return false;
    }
    citizens[citizenCount] = &citizen;
    ++citizenCount;
    return true;
}

bool District::removeCitizenById(int citizenId) {
    for (int i = 0; i < citizenCount; ++i) {
        if (citizens[i] != nullptr && citizens[i]->getId() == citizenId) {
            for (int j = i; j < citizenCount - 1; ++j) {
                citizens[j] = citizens[j + 1];
            }
            citizens[citizenCount - 1] = nullptr;
            --citizenCount;
            return true;
        }
    }
    return false;
}

double District::populationDensity() const {
    if (areaSqKm <= 0.0) {
        return 0.0;
    }
    return static_cast<double>(citizenCount) / areaSqKm;
}
