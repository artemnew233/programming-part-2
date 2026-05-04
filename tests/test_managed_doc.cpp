#include <gtest/gtest.h>
#include "ManagedDocument.h"

TEST(ManagedDocumentTest, BasicAttributes) {
    ManagedDocument md("Report", "Author", "Printer1", "http://link.test", 1);
    EXPECT_EQ(md.getTitle(), "Report");
    EXPECT_EQ(md.getAuthor(), "Author");
    EXPECT_EQ(md.getPrinterTarget(), "Printer1");
    EXPECT_EQ(md.getShareLink(), "http://link.test");
    EXPECT_EQ(md.getVersion(), 1);
}

TEST(ManagedDocumentTest, VersionIncrement) {
    ManagedDocument md("T", "A", "P", "L", 2);
    md.incrementVersion();
    EXPECT_EQ(md.getVersion(), 3);
}

TEST(ManagedDocumentTest, DescribeContainsAllFields) {
    ManagedDocument md("MyDoc", "Writer", "HP", "https://x.com", 5);
    std::string d = md.describe();
    EXPECT_NE(d.find("MyDoc"), std::string::npos);
    EXPECT_NE(d.find("Writer"), std::string::npos);
    EXPECT_NE(d.find("HP"), std::string::npos);
    EXPECT_NE(d.find("https://x.com"), std::string::npos);
}

TEST(DiamondTest, SingleDocumentSubobject) {
    ManagedDocument md("D", "A", "P", "L");
    Document* fromPrintable = static_cast<Printable*>(&md);
    Document* fromShareable = static_cast<Shareable*>(&md);
    Document* fromTrackable = static_cast<Trackable*>(&md);
    EXPECT_EQ(fromPrintable, fromShareable);
    EXPECT_EQ(fromShareable, fromTrackable);
}

TEST(PolymorphismTest, VirtualInfoDispatch) {
    ManagedDocument md("T", "A", "P", "L");
    Document* d = &md;
    EXPECT_EQ(d->getTitle(), "T");
}
