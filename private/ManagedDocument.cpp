#include "ManagedDocument.h"
#include <iostream>
#include <sstream>

ManagedDocument::ManagedDocument(std::string title, std::string author,
                                 std::string printerTarget, std::string shareLink,
                                 int version)
    : Document(std::move(title), std::move(author)), 
      Printable(std::move(printerTarget)),
      Shareable(std::move(shareLink)),
      Trackable(version) {}

std::string ManagedDocument::describe() const {
    std::ostringstream oss;
    oss << "[ManagedDocument] \"" << title_ << "\" by " << author_
        << " | Printer: " << printerTarget_
        << " | Link: " << shareLink_
        << " | v" << version_;
    return oss.str();
}

void ManagedDocument::info() const {
    std::cout << describe() << "\n";
    print();
    share();
    track();
}
