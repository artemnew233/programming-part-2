#include "Document.h"
#include "OfficialDocument.h"
#include "Contract.h"
#include "TechnicalDocument.h"
#include <iostream>

int main() {
    // Base class
    Document doc("Introduction to OOP", "J. Smith");
    doc.printInfo();

    std::cout << "\n--- sizeof analysis ---\n";
    std::cout << "sizeof(Document)         = " << sizeof(Document) << "\n";
    std::cout << "sizeof(OfficialDocument) = " << sizeof(OfficialDocument) << "\n";
    std::cout << "sizeof(Contract)         = " << sizeof(Contract) << "\n";
    std::cout << "sizeof(TechnicalDocument)= " << sizeof(TechnicalDocument) << "\n";

    std::cout << "\n--- Hierarchy demo ---\n";
    OfficialDocument od("Ministry Decree #42", "Ministry of Education",
                        "REG-2024-042", "Ministry of Education");
    od.printInfo();

    Contract c("Software License Agreement", "Legal Dept",
               "CTR-2024-001", "Notary Office",
               "Anthropic Inc.", "OpenAI Ltd.", 50000.0);
    c.printInfo();
    c.sign();
    std::cout << "After signing: " << c.summary() << "\n";

    TechnicalDocument td("API Reference v3", "Dev Team",
                         "Software Engineering", 3);
    td.printInfo();
    td.incrementRevision();
    std::cout << "After revision bump: " << td.summary() << "\n";

    // Polymorphic usage via base pointer
    std::cout << "\n--- Polymorphic call via Document* ---\n";
    Document* docs[] = { &doc, &od, &c, &td };
    for (Document* d : docs) {
        std::cout << d->summary() << "\n";
    }

    return 0;
}
