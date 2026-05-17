#include <gtest/gtest.h>
#include "Document.h"
#include "OfficialDocument.h"
#include "Contract.h"
#include "TechnicalDocument.h"

TEST(ContractTest, DescribeBeforeSign) {
    Contract c("Deal", "Dept", "C-001", "Notary", "A", "B", 999.0);
    EXPECT_NE(c.describe().find("PENDING"), std::string::npos);
}

TEST(ContractTest, DescribeAfterSign) {
    Contract c("Deal", "Dept", "C-001", "Notary", "A", "B", 999.0);
    c.sign();
    EXPECT_NE(c.describe().find("SIGNED"), std::string::npos);
}

TEST(TechnicalDocumentTest, RevisionIncrement) {
    TechnicalDocument td("Spec", "Eng", "HW", 1);
    td.incrementRevision();
    EXPECT_EQ(td.getRevision(), 2);
}

TEST(PolymorphismTest, VirtualDispatchWorksCorrectly) {
    Contract c("C", "A", "R", "I", "X", "Y", 0.0);
    TechnicalDocument td("T", "A", "D", 1);
    OfficialDocument od("O", "A", "R2", "I2");

    Document* arr[] = { &c, &td, &od };
    EXPECT_EQ(arr[0]->getType(), "Contract");
    EXPECT_EQ(arr[1]->getType(), "TechnicalDocument");
    EXPECT_EQ(arr[2]->getType(), "OfficialDocument");
}

TEST(AbstractTest, ContractIsConcreteDocumentSubtype) {
    // This test verifies the hierarchy is correct at compile time
    Contract c("T", "A", "R", "I", "P1", "P2", 100.0);
    Document* d = &c;
    EXPECT_EQ(d->getType(), "Contract");
}
