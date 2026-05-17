#include "Trackable.h"
#include <iostream>
#include <sstream>

Trackable::Trackable(int version)
    : version_(version) {}

int Trackable::getVersion() const { return version_; }
void Trackable::incrementVersion() { ++version_; }

void Trackable::track() const {
    std::cout << "[TRACK] \"" << title_ << "\" version=" << version_ << "\n";
}

std::string Trackable::describe() const {
    return Document::describe() + " | v" + std::to_string(version_);
}
