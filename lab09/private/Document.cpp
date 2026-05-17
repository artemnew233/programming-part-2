#include "Document.h"
#include <iostream>
#include <sstream>

Document::Document(std::string title, std::string author)
    : title_(std::move(title)), author_(std::move(author)) {}

std::string Document::getTitle() const { return title_; }
std::string Document::getAuthor() const { return author_; }

std::string Document::describe() const {
    return "[Document] \"" + title_ + "\" by " + author_;
}

void Document::info() const {
    std::cout << describe() << "\n";
}
