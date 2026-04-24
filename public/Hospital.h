#ifndef HOSPITAL_H
#define HOSPITAL_H


class Hospital {
private:
    int         id;
    const char* name;
    int         capacity;
    bool        isPublic;

public:
    Hospital();
    Hospital(int id, const char* name, int capacity, bool isPublic);

    int         getId()       const;
    const char* getName()     const;
    int         getCapacity() const;
    bool        getIsPublic() const;

    bool isLargeHospital() const;
};

#endif
