#pragma once
#include "OfficialDocument.h"

class Contract final : public OfficialDocument {
public:
    Contract(std::string title, std::string author,
             std::string registrationId, std::string issuingAuthority,
             std::string partyA, std::string partyB, double value);

    const std::string& getPartyA() const;
    const std::string& getPartyB() const;
    double getValue() const;
    bool isSigned() const;
    void sign();

    std::string getType() const override;
    std::string summary() const override;

private:
    std::string partyA_;
    std::string partyB_;
    double value_;
    bool signed_ = false;
};
