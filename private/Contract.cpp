#include "Contract.h"
#include <sstream>

Contract::Contract(std::string title, std::string author,
                   std::string registrationId, std::string issuingAuthority,
                   std::string partyA, std::string partyB, double value)
    : OfficialDocument(std::move(title), std::move(author),
                       std::move(registrationId), std::move(issuingAuthority)),
      partyA_(std::move(partyA)), partyB_(std::move(partyB)), value_(value) {}

const std::string& Contract::getPartyA() const { return partyA_; }
const std::string& Contract::getPartyB() const { return partyB_; }
double Contract::getValue() const { return value_; }
bool Contract::isSigned() const { return signed_; }
void Contract::sign() { signed_ = true; }
std::string Contract::getType() const { return "Contract"; }

std::string Contract::summary() const {
    std::ostringstream oss;
    oss << OfficialDocument::summary()
        << " | " << partyA_ << " <-> " << partyB_
        << " | Value: " << value_
        << " | " << (signed_ ? "SIGNED" : "UNSIGNED");
    return oss.str();
}
