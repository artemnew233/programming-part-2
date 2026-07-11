#ifndef SCHOOL_H
#define SCHOOL_H

// School exists independently; City only holds a reference to it.
class School {
private:
    int         id;
    const char* name;
    int         capacity;
    const char* level; // "primary" | "secondary"

public:
    School();
    School(int id, const char* name, int capacity, const char* level);

    int         getId()       const;
    const char* getName()     const;
    int         getCapacity() const;
    const char* getLevel()    const;

    bool isPrimary() const;
};

#endif
