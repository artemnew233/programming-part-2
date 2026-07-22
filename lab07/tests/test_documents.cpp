#include <gtest/gtest.h>
#include "Document.h"
#include "OfficialDocument.h"
#include "Contract.h"
#include "TechnicalDocument.h"

TEST(DocumentTest, BasicGetters) {
    Document d("Title", "Author");
    EXPECT_EQ(d.getTitle(), "Title");
    EXPECT_EQ(d.getAuthor(), "Author");
    EXPECT_EQ(d.getType(), "Document");
}

TEST(OfficialDocumentTest, RegistrationAndAuthority) {
    OfficialDocument od("Decree", "Gov", "R-001", "Ministry");
    EXPECT_EQ(od.getRegistrationId(), "R-001");
    EXPECT_EQ(od.getIssuingAuthority(), "Ministry");
    EXPECT_TRUE(od.isRegistered());
    EXPECT_EQ(od.getType(), "OfficialDocument");
}

TEST(ContractTest, SigningWorkflow) {
    Contract c("Deal", "Dept", "C-001", "Notary", "A Corp", "B Corp", 1000.0);
    EXPECT_FALSE(c.isSigned());
    c.sign();
    EXPECT_TRUE(c.isSigned());
    EXPECT_DOUBLE_EQ(c.getValue(), 1000.0);
    EXPECT_EQ(c.getType(), "Contract");
}

TEST(ContractTest, SummaryContainsParties) {
    Contract c("Deal", "Dept", "C-002", "Notary", "Alice", "Bob", 500.0);
    std::string s = c.summary();
    EXPECT_NE(s.find("Alice"), std::string::npos);
    EXPECT_NE(s.find("Bob"), std::string::npos);
}

TEST(TechnicalDocumentTest, RevisionIncrement) {
    TechnicalDocument td("Spec", "Engineer", "Hardware", 1);
    EXPECT_EQ(td.getRevision(), 1);
    td.incrementRevision();
    EXPECT_EQ(td.getRevision(), 2);
    EXPECT_EQ(td.getType(), "TechnicalDocument");
}

TEST(SizeofTest, HierarchySizeGrows) {
    EXPECT_LE(sizeof(Document), sizeof(OfficialDocument));
    EXPECT_LE(sizeof(OfficialDocument), sizeof(Contract));
}
