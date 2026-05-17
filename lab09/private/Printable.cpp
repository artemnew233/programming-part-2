#include "Printable.h"
#include <iostream>

Printable::Printable(std::string printerTarget)
    : printerTarget_(std::move(printerTarget)) {}

std::string Printable::getPrinterTarget() const { return printerTarget_; }

void Printable::print() const {
    std::cout << "[PRINT] Sending \"" << title_ << "\" to " << printerTarget_ << "\n";
}

std::string Printable::describe() const {
    return Document::describe() + " | Printer: " + printerTarget_;
}
