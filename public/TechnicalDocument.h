#pragma once
#include "Document.h"

class TechnicalDocument final : public Document {
public:
    TechnicalDocument(std::string title, std::string author,
                      std::string domain, int revision = 1);

    void incrementRevision();
    int getRevision() const;
    const std::string& getDomain() const;

    std::string getType() const override;
    std::string describe() const override;

private:
    std::string domain_;
    int revision_;
};
