#pragma once
#include <string>

class Leaf {
public:
    explicit Leaf(double lengthCm, std::string color = "green");
    double getLength() const;
    const std::string& getColor() const;
    bool isHealthy() const;
    std::string describe() const;
private:
    double lengthCm_;
    std::string color_;
};
