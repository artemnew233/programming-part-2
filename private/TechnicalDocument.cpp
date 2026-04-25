#include "TechnicalDocument.h"
#include <sstream>

TechnicalDocument::TechnicalDocument(std::string title, std::string author,
                                     std::string domain, int revisionNumber)
    : Document(std::move(title), std::move(author)),
      domain_(std::move(domain)), revisionNumber_(revisionNumber) {}

const std::string& TechnicalDocument::getDomain() const { return domain_; }
int TechnicalDocument::getRevision() const { return revisionNumber_; }
void TechnicalDocument::incrementRevision() { ++revisionNumber_; }
std::string TechnicalDocument::getType() const { return "TechnicalDocument"; }

std::string TechnicalDocument::summary() const {
    std::ostringstream oss;
    oss << Document::summary()
        << " | Domain: " << domain_ << " | Rev: " << revisionNumber_;
    return oss.str();
}
