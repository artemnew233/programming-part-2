#pragma once
#include "OfficialDocument.h"

class Contract final : public OfficialDocument {
public:
    Contract(std::string title, std::string author,
             std::string registrationId, std::string issuingAuthority,
             std::string partyA, std::string partyB, double value);

    void sign();
    bool isSigned() const;
    double getValue() const;

    std::string getType() const override;
    std::string describe() const override;

private:
    std::string partyA_;
    std::string partyB_;
    double value_;
    bool signed_ = false;
};
