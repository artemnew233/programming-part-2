#pragma once
#include "Document.h"

class TechnicalDocument : public Document {
public:
    TechnicalDocument(std::string title, std::string author,
                      std::string domain, int revisionNumber = 1);

    const std::string& getDomain() const;
    int getRevision() const;
    void incrementRevision();

    std::string getType() const override;
    std::string summary() const override;

private:
    std::string domain_;
    int revisionNumber_;
};
