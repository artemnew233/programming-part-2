#include "OfficialDocument.h"
#include <sstream>

OfficialDocument::OfficialDocument(std::string title, std::string author,
                                   std::string registrationId, std::string issuingAuthority)
    : Document(std::move(title), std::move(author)),
      registrationId_(std::move(registrationId)),
      issuingAuthority_(std::move(issuingAuthority)) {}

const std::string& OfficialDocument::getRegistrationId() const { return registrationId_; }
const std::string& OfficialDocument::getIssuingAuthority() const { return issuingAuthority_; }
std::string OfficialDocument::getType() const { return "OfficialDocument"; }

std::string OfficialDocument::describe() const {
    std::ostringstream oss;
    oss << "[" << getType() << "] " << title_ << " | "
        << "Reg: " << registrationId_ << " | Issued by: " << issuingAuthority_;
    return oss.str();
}
