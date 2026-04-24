#ifndef CITIZEN_H
#define CITIZEN_H


class Citizen {
private:
    int         id;
    const char* fullName;
    int         age;
    int         districtId;

public:
    Citizen();
    Citizen(int id, const char* fullName, int age, int districtId);

    int         getId()         const;
    const char* getFullName()   const;
    int         getAge()        const;
    int         getDistrictId() const;

    void setDistrictId(int newDistrictId);
    bool isAdult() const;
};

#endif