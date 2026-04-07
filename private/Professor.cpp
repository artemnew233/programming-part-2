#include "../public/Professor.h"

Professor::Professor(const std::string& name, const std::string& rank) : name(name), rank(rank) {}

std::string Professor::getName() const {
    return name;
}

std::string Professor::getRank() const {
    return rank;
}
