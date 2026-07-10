#pragma once
#include "Document.h"

class Shareable : public virtual Document {
public:
    Shareable(std::string shareLink = "");
    virtual void share() const;
    std::string getShareLink() const;
    std::string describe() const override;
protected:
    std::string shareLink_;
};
