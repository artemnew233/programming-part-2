#include "Document.h"
#include "OfficialDocument.h"
#include "Contract.h"
#include "TechnicalDocument.h"
#include <iostream>

int main() {
    Contract c("Service Agreement", "Legal",
               "C-2024-001", "City Notary",
               "TechCorp", "ClientLtd", 75000.0);
    c.sign();

    OfficialDocument od("Official Notice", "Gov Office",
                        "N-2024-100", "Ministry");

    TechnicalDocument td("System Architecture v2", "Arch Team",
                         "Backend", 2);
    td.incrementRevision();

    const int N = 3;
    Document* docs[N] = { &c, &od, &td };

    std::cout << "=== Polymorphic describe() via Document* ===\n";
    for (int i = 0; i < N; ++i) {
        docs[i]->print();  
    }

    std::cout << "\n=== sizeof analysis ===\n";
    std::cout << "sizeof(Document)         = " << sizeof(Document) << "\n";
    std::cout << "sizeof(OfficialDocument) = " << sizeof(OfficialDocument) << "\n";
    std::cout << "sizeof(Contract)         = " << sizeof(Contract) << "\n";
    std::cout << "sizeof(TechnicalDocument)= " << sizeof(TechnicalDocument) << "\n";


    return 0;
}
