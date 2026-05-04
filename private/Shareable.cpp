#include "Shareable.h"
#include <iostream>

Shareable::Shareable(std::string shareLink)
    : shareLink_(std::move(shareLink)) {}

std::string Shareable::getShareLink() const { return shareLink_; }

void Shareable::share() const {
    std::cout << "[SHARE] Sharing \"" << title_ << "\" via " << shareLink_ << "\n";
}

std::string Shareable::describe() const {
    return Document::describe() + " | Link: " + shareLink_;
}
