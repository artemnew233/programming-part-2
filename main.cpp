#include "Document.h"
#include "Printable.h"
#include "Shareable.h"
#include "Trackable.h"
#include "ManagedDocument.h"
#include <iostream>

int main() {
    ManagedDocument md("Annual Report 2024",
                       "Finance Team",
                       "LaserJet-3F",
                       "https://share.example.com/annual2024",
                       1);

    std::cout << "=== ManagedDocument full info ===\n";
    md.info();
    md.incrementVersion();
    std::cout << "\nAfter version bump:\n" << md.describe() << "\n";

    std::cout << "\n=== sizeof analysis ===\n";
    std::cout << "sizeof(Document)         = " << sizeof(Document) << "\n";
    std::cout << "sizeof(Printable)        = " << sizeof(Printable) << "\n";
    std::cout << "sizeof(Shareable)        = " << sizeof(Shareable) << "\n";
    std::cout << "sizeof(Trackable)        = " << sizeof(Trackable) << "\n";
    std::cout << "sizeof(ManagedDocument)  = " << sizeof(ManagedDocument) << "\n";

    std::cout << "\n=== Polymorphic dispatch ===\n";
    Document* docs[] = { &md };
    for (auto* d : docs) {
        d->info(); 
    }

    Printable* p = &md;
    p->print();

    Shareable* s = &md;
    s->share();

    Trackable* t = &md;
    t->track();

    return 0;
}
