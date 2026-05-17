#include "TechnicalDocument.h"
#include <sstream>

TechnicalDocument::TechnicalDocument(std::string title, std::string author,
                                     std::string domain, int revision)
    : Document(std::move(title), std::move(author)),
      domain_(std::move(domain)), revision_(revision) {}

void TechnicalDocument::incrementRevision() { ++revision_; }
int TechnicalDocument::getRevision() const { return revision_; }
const std::string& TechnicalDocument::getDomain() const { return domain_; }
std::string TechnicalDocument::getType() const { return "TechnicalDocument"; }

std::string TechnicalDocument::describe() const {
    std::ostringstream oss;
    oss << "[TechnicalDocument] " << title_
        << " | Domain: " << domain_ << " | Rev." << revision_;
    return oss.str();
}
