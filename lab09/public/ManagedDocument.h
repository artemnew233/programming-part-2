#pragma once
#include "Printable.h"
#include "Shareable.h"
#include "Trackable.h"

class ManagedDocument final : public Printable, public Shareable, public Trackable {
public:
    ManagedDocument(std::string title, std::string author,
                    std::string printerTarget, std::string shareLink,
                    int version = 1);

    void info() const override;
    std::string describe() const override;
};
