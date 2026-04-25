#include "Contract.h"
#include <sstream>

Contract::Contract(std::string title, std::string author,
                   std::string registrationId, std::string issuingAuthority,
                   std::string partyA, std::string partyB, double value)
    : OfficialDocument(std::move(title), std::move(author),
                       std::move(registrationId), std::move(issuingAuthority)),
      partyA_(std::move(partyA)), partyB_(std::move(partyB)), value_(value) {}

void Contract::sign() { signed_ = true; }
bool Contract::isSigned() const { return signed_; }
double Contract::getValue() const { return value_; }
std::string Contract::getType() const { return "Contract"; }

std::string Contract::describe() const {
    std::ostringstream oss;
    oss << "[Contract] " << title_
        << " | " << partyA_ << " <-> " << partyB_
        << " | $" << value_
        << " | " << (signed_ ? "SIGNED" : "PENDING");
    return oss.str();
}
