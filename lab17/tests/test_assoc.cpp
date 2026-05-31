#include "FileRecord.hpp"

#include <gtest/gtest.h>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static const auto DATA = makeDataset();

TEST(AssocTest, MapIndexByName) {
    std::map<std::string, FileRecord> byName;
    for (const auto& r : DATA) byName.emplace(r.name, r);

    EXPECT_TRUE(byName.contains("config"));
    EXPECT_EQ(byName.at("config").id, 2);
    EXPECT_FALSE(byName.contains("doesnotexist"));
}

TEST(AssocTest, MapAtThrowsOnMissingKey) {
    std::map<std::string, FileRecord> byName;
    byName.emplace("report", DATA[0]);
    EXPECT_THROW((void)byName.at("missing"), std::out_of_range);
}

TEST(AssocTest, SetUniqueExtensions) {
    std::set<std::string> extensions;
    for (const auto& r : DATA) extensions.insert(r.extension);
    EXPECT_GE(extensions.size(), 5u);
    EXPECT_TRUE(extensions.contains(".txt"));
    EXPECT_TRUE(extensions.contains(".json"));
    EXPECT_FALSE(extensions.contains(".exe"));
}

TEST(AssocTest, SetOrderedTraversal) {
    std::set<std::string> extensions;
    for (const auto& r : DATA) extensions.insert(r.extension);
    std::string prev;
    for (const auto& e : extensions) {
        EXPECT_LE(prev, e);
        prev = e;
    }
}

TEST(AssocTest, MultimapGroupByExtension) {
    std::multimap<std::string, int> idsByExt;
    for (const auto& r : DATA) idsByExt.emplace(r.extension, r.id);

    const auto [first, last] = idsByExt.equal_range(".txt");
    int count = static_cast<int>(std::distance(first, last));
    EXPECT_GT(count, 1);
}

TEST(AssocTest, FrequencyTable) {
    std::map<std::string, int> freq;
    for (const auto& r : DATA) ++freq[r.extension];
    EXPECT_GT(freq[".txt"],  0);
    EXPECT_GT(freq[".json"], 0);
    EXPECT_GT(freq[".csv"],  0);
}

TEST(AssocTest, UnorderedMapById) {
    std::unordered_map<int, const FileRecord*> byId;
    byId.reserve(DATA.size());
    for (const auto& r : DATA) byId.emplace(r.id, &r);

    EXPECT_TRUE(byId.contains(1));
    EXPECT_EQ(byId.at(2)->extension, ".json");
    EXPECT_FALSE(byId.contains(999));
}

TEST(AssocTest, UnorderedMapLoadFactor) {
    std::unordered_map<int, int> m;
    m.max_load_factor(0.5f);
    for (int i = 0; i < 100; ++i) m[i] = i;
    EXPECT_LE(m.load_factor(), 0.5f + 0.01f);
}

TEST(AssocTest, InsertionAndRemoval) {
    std::map<std::string, FileRecord> byName;
    for (const auto& r : DATA) byName.emplace(r.name, r);

    byName.emplace("newfile", FileRecord{99, "newfile", ".txt", 1024, false});
    EXPECT_TRUE(byName.contains("newfile"));
    byName.erase("newfile");
    EXPECT_FALSE(byName.contains("newfile"));
}

TEST(AssocTest, ReadonlyFrequency) {
    std::map<bool, int> freq;
    for (const auto& r : DATA) ++freq[r.readonly];
    EXPECT_GT(freq[false], 0);
    EXPECT_GT(freq[true],  0);
    EXPECT_EQ(freq[true] + freq[false], static_cast<int>(DATA.size()));
}
