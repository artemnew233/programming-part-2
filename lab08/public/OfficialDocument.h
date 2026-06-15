#pragma once
#include "Document.h"

class OfficialDocument : public Document {
public:
    OfficialDocument(std::string title, std::string author,
                     std::string registrationId, std::string issuingAuthority);

    const std::string& getRegistrationId() const;
    const std::string& getIssuingAuthority() const;

    // Still abstract — does not implement getType() or describe() fully;
    // subclasses must finish. Actually both are implemented here to allow
    // OfficialDocument to be concrete if desired, but Contract overrides them.
    std::string getType() const override;
    std::string describe() const override;

protected:
    std::string registrationId_;
    std::string issuingAuthority_;
};
