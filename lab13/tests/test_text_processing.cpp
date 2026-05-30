#include <gtest/gtest.h>
#include "Record.h"
#include "ReportBuilder.h"
#include "StringUtils.h"

// ── trim / split / parseKeyValue ──────────────────────────────────────

TEST(StringUtilsTest, TrimRemovesWhitespace) {
    EXPECT_EQ(trim("  hello  "), "hello");
    EXPECT_EQ(trim("\t\nhi\n"), "hi");
    EXPECT_EQ(trim("   "), "");
}

TEST(StringUtilsTest, SplitBySemicolon) {
    const auto parts = split("a=1; b=2; c=3", ';');
    ASSERT_EQ(parts.size(), 3u);
    EXPECT_EQ(parts[0], "a=1");
    EXPECT_EQ(parts[1], "b=2");
}

TEST(StringUtilsTest, ParseKeyValueValid) {
    std::string k, v;
    EXPECT_TRUE(parseKeyValue("name=report.txt", k, v));
    EXPECT_EQ(k, "name");
    EXPECT_EQ(v, "report.txt");
}

TEST(StringUtilsTest, ParseKeyValueNoEquals) {
    std::string k, v;
    EXPECT_FALSE(parseKeyValue("noequals", k, v));
}

TEST(StringUtilsTest, ParseLongLongValid) {
    long long v{};
    EXPECT_TRUE(parseLongLong("2048", v));
    EXPECT_EQ(v, 2048);
}

TEST(StringUtilsTest, ParseLongLongRejectsPartial) {
    long long v{};
    EXPECT_FALSE(parseLongLong("24abc", v));
}

// ── trim_view / split_view / parseKeyValueView ─────────────────────────

TEST(StringViewTest, TrimView) {
    const std::string s = "  hello  ";
    EXPECT_EQ(trim_view(s), "hello");
}

TEST(StringViewTest, SplitView) {
    const std::string s = "a=1; b=2";
    const auto parts = split_view(s, ';');
    ASSERT_EQ(parts.size(), 2u);
    EXPECT_EQ(parts[0], "a=1");
}

TEST(StringViewTest, ParseKeyValueView) {
    const std::string s = "size=4096";
    std::string_view k, v;
    EXPECT_TRUE(parseKeyValueView(s, k, v));
    EXPECT_EQ(k, "size");
    EXPECT_EQ(v, "4096");
}

// ── parseRecord ───────────────────────────────────────────────────────

TEST(RecordTest, ValidLine) {
    FileRecord r; std::string err;
    EXPECT_TRUE(parseRecord("name=report.txt; size=2048; type=text; readonly=no", r, err));
    EXPECT_EQ(r.name,     "report.txt");
    EXPECT_EQ(r.size,     2048);
    EXPECT_EQ(r.type,     "text");
    EXPECT_FALSE(r.readonly);
}

TEST(RecordTest, ReadonlyYes) {
    FileRecord r; std::string err;
    EXPECT_TRUE(parseRecord("name=config.json; size=512; type=json; readonly=yes", r, err));
    EXPECT_TRUE(r.readonly);
}

TEST(RecordTest, EmptyNameInvalid) {
    FileRecord r; std::string err;
    EXPECT_FALSE(parseRecord("name=; size=1024; type=text; readonly=no", r, err));
    EXPECT_FALSE(err.empty());
}

TEST(RecordTest, InvalidSizeInvalid) {
    FileRecord r; std::string err;
    EXPECT_FALSE(parseRecord("name=db.db; size=abc; type=database; readonly=no", r, err));
}

TEST(RecordTest, NegativeSizeInvalid) {
    FileRecord r; std::string err;
    EXPECT_FALSE(parseRecord("name=video.mp4; size=-100; type=video; readonly=no", r, err));
}

TEST(RecordTest, InvalidReadonlyValue) {
    FileRecord r; std::string err;
    EXPECT_FALSE(parseRecord("name=index.html; size=2048; type=text; readonly=invalid", r, err));
}

TEST(RecordTest, MissingField) {
    FileRecord r; std::string err;
    EXPECT_FALSE(parseRecord("name=notes.md; size=256; type=text", r, err));
    EXPECT_NE(err.find("missing"), std::string::npos);
}

TEST(RecordTest, NoExtensionInvalid) {
    FileRecord r; std::string err;
    EXPECT_FALSE(parseRecord("name=readme; size=512; type=text; readonly=no", r, err));
}

// ── regex helpers ─────────────────────────────────────────────────────

TEST(RegexTest, NormalizeSpaces) {
    EXPECT_EQ(normalizeSpaces("a  b   c"), "a b c");
}

TEST(RegexTest, ValidateFileName) {
    EXPECT_TRUE(validateFileName("report.txt"));
    EXPECT_TRUE(validateFileName("photo.jpg"));
    EXPECT_FALSE(validateFileName("readme"));
}

TEST(RegexTest, MaskLargeIds) {
    EXPECT_EQ(maskLargeIds("file_1234567_x.zip"), "file_[id]_x.zip");
    EXPECT_EQ(maskLargeIds("file_123.zip"), "file_123.zip"); // short — not masked
}
