#ifndef SEAT_H
#define SEAT_H

#include <string>

class Seat {
public:
    Seat(const std::string& material, bool heated);
    std::string getMaterial() const;
    bool isHeated() const;
    void adjust(int position);

private:
    std::string material;
    bool heated;
    int position;
};

#endif
