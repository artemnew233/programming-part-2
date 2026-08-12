#include "Leaf.h"
#include <sstream>

Leaf::Leaf(double lengthCm, std::string color)
    : lengthCm_(lengthCm), color_(std::move(color)) {}

double Leaf::getLength() const { return lengthCm_; }
const std::string& Leaf::getColor() const { return color_; }
bool Leaf::isHealthy() const { return color_ == "green" && lengthCm_ > 0.5; }

std::string Leaf::describe() const {
    std::ostringstream oss;
    oss << "Leaf[" << color_ << ", " << lengthCm_ << "cm, "
        << (isHealthy() ? "healthy" : "unhealthy") << "]";
    return oss.str();
}
