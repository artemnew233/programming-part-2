#include "Fruit.h"
#include <sstream>

Fruit::Fruit(std::string type, double weightGrams)
    : type_(std::move(type)), weightGrams_(weightGrams) {}

const std::string& Fruit::getType() const { return type_; }
double Fruit::getWeight() const { return weightGrams_; }

std::string Fruit::describe() const {
    std::ostringstream oss;
    oss << "Fruit[" << type_ << ", " << weightGrams_ << "g]";
    return oss.str();
}
