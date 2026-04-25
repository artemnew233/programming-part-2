#pragma once
#include "Document.h"

class OfficialDocument : public Document {
public:
    OfficialDocument(std::string title, std::string author,
                     std::string registrationId, std::string issuingAuthority);

    const std::string& getRegistrationId() const;
    const std::string& getIssuingAuthority() const;
    bool isRegistered() const;

    std::string getType() const override;
    std::string summary() const override;

protected:
    std::string registrationId_;
    std::string issuingAuthority_;
};
