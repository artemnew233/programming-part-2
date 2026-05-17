#include "Root.h"
#include <sstream>

Root::Root(double depthCm, std::string type)
    : depthCm_(depthCm), type_(std::move(type)) {}

double Root::getDepth() const { return depthCm_; }
const std::string& Root::getType() const { return type_; }
double Root::waterAbsorptionRate() const { return depthCm_ * 0.05; }

std::string Root::describe() const {
    std::ostringstream oss;
    oss << "Root[" << type_ << ", depth=" << depthCm_ << "cm, "
        << "absorption=" << waterAbsorptionRate() << "L/h]";
    return oss.str();
}
