#pragma once
#include "Document.h"

class Printable : public virtual Document {
public:
    Printable(std::string printerTarget = "default");
    virtual void print() const;
    std::string getPrinterTarget() const;
    std::string describe() const override;
protected:
    std::string printerTarget_;
};
