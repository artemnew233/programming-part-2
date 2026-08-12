#pragma once
#include <string>

class Fruit {
public:
    explicit Fruit(std::string type, double weightGrams = 10.0);
    const std::string& getType() const;
    double getWeight() const;
    std::string describe() const;
private:
    std::string type_;
    double weightGrams_;
};
