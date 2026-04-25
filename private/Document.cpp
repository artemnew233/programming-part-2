#include "Document.h"
#include <sstream>
#include <iostream>

Document::Document(std::string title, std::string author, std::time_t created)
    : title_(std::move(title)), author_(std::move(author)), createdAt_(created) {}

const std::string& Document::getTitle() const { return title_; }
const std::string& Document::getAuthor() const { return author_; }
std::time_t Document::getCreatedAt() const { return createdAt_; }
std::string Document::getType() const { return "Document"; }

std::string Document::summary() const {
    std::ostringstream oss;
    oss << "[" << getType() << "] \"" << title_ << "\" by " << author_;
    return oss.str();
}

void Document::printInfo() const {
    std::cout << summary() << "\n";
}
