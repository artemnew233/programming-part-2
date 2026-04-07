#ifndef WHEEL_H
#define WHEEL_H

#include <string>

class Wheel {
public:
    Wheel(int size, const std::string& tireType);
    int getSize() const;
    std::string getTireType() const;
    void rotate();

private:
    int size;
    std::string tireType;
};

#endif
