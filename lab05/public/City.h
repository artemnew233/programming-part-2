#ifndef CITY_H
#define CITY_H

#include "District.h"
#include "Hospital.h"
#include "School.h"


class City {
private:
    static const int MAX_DISTRICTS = 5;
    static const int MAX_HOSPITALS = 5;
    static const int MAX_SCHOOLS   = 5;

    const char* name;
    int         population;

    District* districts[MAX_DISTRICTS];
    Hospital* hospitals[MAX_HOSPITALS];
    School*   schools[MAX_SCHOOLS];

    int districtCount;
    int hospitalCount;
    int schoolCount;

public:
    City();
    City(const char* name, int population);

    const char* getName()          const;
    int         getPopulation()    const;
    int         getDistrictCount() const;
    int         getHospitalCount() const;
    int         getSchoolCount()   const;

    const District* getDistrictAt(int index) const;
    const Hospital* getHospitalAt(int index) const;
    const School*   getSchoolAt(int index)   const;

    bool addDistrict(District& district);
    bool addHospital(Hospital& hospital);
    bool addSchool(School& school);

    bool hasDistrict(int districtId) const;
    bool hasHospital(int hospitalId) const;
    bool hasSchool(int schoolId)     const;

    int totalPublicHospitals() const;
};

#endif
