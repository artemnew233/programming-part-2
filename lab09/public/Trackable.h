#pragma once
#include "Document.h"

class Trackable : public virtual Document {
public:
    Trackable(int version = 1);
    virtual void track() const;
    int getVersion() const;
    void incrementVersion();
    std::string describe() const override;
protected:
    int version_;
};
