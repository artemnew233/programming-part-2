#ifndef DISTRICT_H
#define DISTRICT_H

#include "Citizen.h"

class District {
private:
    static const int MAX_CITIZENS = 10;

    int         id;
    const char* name;
    double      areaSqKm;
    Citizen*    citizens[MAX_CITIZENS];
    int         citizenCount;

public:
    District();
    District(int id, const char* name, double areaSqKm);

    int         getId()          const;
    const char* getName()        const;
    double      getAreaSqKm()    const;
    int         getCitizenCount()const;
    const Citizen* getCitizenAt(int index) const;

    bool addCitizen(Citizen& citizen);
    bool removeCitizenById(int citizenId);
    bool containsCitizen(int citizenId) const;

    double populationDensity() const;
};

#endif
