#include "Document.h"
#include <iostream>

Document::Document(std::string title, std::string author)
    : title_(std::move(title)), author_(std::move(author)) {}

const std::string& Document::getTitle() const { return title_; }
const std::string& Document::getAuthor() const { return author_; }

void Document::print() const {
    std::cout << describe() << "\n";
}
