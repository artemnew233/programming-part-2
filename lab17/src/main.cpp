#include "FileRecord.hpp"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// ── Extension 1: composite key + hash/equality ─────────────────────────
struct FileKey {
    std::string name;
    std::string extension;
};

struct FileKeyHash {
    std::size_t operator()(const FileKey& k) const noexcept {
        const std::size_t h1 = std::hash<std::string>{}(k.name);
        const std::size_t h2 = std::hash<std::string>{}(k.extension);
        return h1 ^ (h2 << 1u);
    }
};

struct FileKeyEqual {
    bool operator()(const FileKey& a, const FileKey& b) const noexcept {
        return a.name == b.name && a.extension == b.extension;
    }
};

// ── Extension 2: priority queue comparator ─────────────────────────────
struct LargerFirst {
    bool operator()(const FileRecord& a, const FileRecord& b) const noexcept {
        return a.size < b.size;
    }
};

int main() {
    const auto records = makeDataset();

    // ── index by name (unique key) ─────────────────────────────────────
    std::map<std::string, FileRecord> byName;
    for (const auto& r : records)
        byName.emplace(r.name, r);

    std::cout << "=== Index by name (ordered) ===\n";
    if (const auto it = byName.find("config"); it != byName.end())
        std::cout << "config: id=" << it->second.id << " ext=" << it->second.extension << '\n';

    // ── set of unique extensions ───────────────────────────────────────
    std::set<std::string> extensions;
    for (const auto& r : records)
        extensions.insert(r.extension);

    std::cout << "\n=== Unique extensions (ordered) ===\n";
    for (const auto& e : extensions) std::cout << "  " << e << '\n';

    // ── multimap: grouping by extension ───────────────────────────────
    std::multimap<std::string, int> idsByExt;
    for (const auto& r : records)
        idsByExt.emplace(r.extension, r.id);

    std::cout << "\n=== Files grouped by .jpg ===\n";
    const auto [first, last] = idsByExt.equal_range(".jpg");
    for (auto it = first; it != last; ++it)
        std::cout << "  id=" << it->second << '\n';

    // ── frequency table: extension -> count ───────────────────────────
    std::map<std::string, int> extFreq;
    for (const auto& r : records) ++extFreq[r.extension];

    std::cout << "\n=== Extension frequency ===\n";
    for (const auto& [ext, cnt] : extFreq)
        std::cout << "  " << std::left << std::setw(8) << ext << cnt << '\n';

    // ── frequency table: readonly status ──────────────────────────────
    std::map<bool, int> roFreq;
    for (const auto& r : records) ++roFreq[r.readonly];
    std::cout << "\nReadonly: " << roFreq[true]  << " | Writable: " << roFreq[false] << '\n';

    // ── unordered_map: fast stock index by id ─────────────────────────
    std::unordered_map<int, const FileRecord*> byId;
    byId.reserve(records.size());
    byId.max_load_factor(0.7f);
    for (const auto& r : records) byId.emplace(r.id, &r);

    std::cout << "\n=== Unordered index by id ===\n";
    std::cout << "bucket_count=" << byId.bucket_count()
              << " load_factor=" << byId.load_factor() << '\n';

    if (const auto it = byId.find(10); it != byId.end())
        std::cout << "id=10: " << it->second->name << it->second->extension << '\n';

    // ── ordered vs unordered traversal ────────────────────────────────
    std::cout << "\n=== Ordered traversal (first 5 by name) ===\n";
    int n = 0;
    for (const auto& [name, rec] : byName) {
        if (++n > 5) break;
        std::cout << "  " << name << '\n';
    }

    std::cout << "\n=== Unordered traversal (first 5 by id) ===\n";
    n = 0;
    for (const auto& [id, ptr] : byId) {
        if (++n > 5) break;
        std::cout << "  id=" << id << " " << ptr->name << '\n';
    }

    // ── insertion & removal ────────────────────────────────────────────
    byName.emplace("newfile", FileRecord{26, "newfile", ".txt", 1024, false});
    assert(byName.contains("newfile"));
    byName.erase("newfile");
    assert(!byName.contains("newfile"));

    // ── set operations ─────────────────────────────────────────────────
    const std::set<std::string> expected{".csv", ".json", ".txt", ".xml"};
    std::vector<std::string> missing;
    std::set_difference(expected.begin(), expected.end(),
                        extensions.begin(), extensions.end(),
                        std::back_inserter(missing));
    std::cout << "\n=== Missing expected extensions ===\n";
    for (const auto& e : missing) std::cout << "  " << e << '\n';

    // ── Extension 1: composite key in unordered_set ────────────────────
    std::unordered_set<FileKey, FileKeyHash, FileKeyEqual> keySet;
    for (const auto& r : records) keySet.insert({r.name, r.extension});

    std::cout << "\n=== Extension 1: composite key lookup ===\n";
    std::cout << "contains {report,.txt}: "
              << keySet.contains({"report", ".txt"}) << '\n';
    std::cout << "contains {report,.csv}: "
              << keySet.contains({"report", ".csv"}) << '\n';

    // ── Extension 2: priority_queue — largest file first ───────────────
    std::priority_queue<FileRecord, std::vector<FileRecord>, LargerFirst> pq;
    for (const auto& r : records) pq.push(r);

    std::cout << "\n=== Extension 2: top 3 largest files ===\n";
    for (int i = 0; i < 3 && !pq.empty(); ++i) {
        const auto& top = pq.top();
        std::cout << "  " << top.name << top.extension
                  << " " << top.size << "b\n";
        pq.pop();
    }

    // ── control checks ─────────────────────────────────────────────────
    assert(byName.contains("config"));
    assert(byName.at("config").id == 2);
    assert(extensions.size() >= 5u);
    assert(byId.contains(1));
    assert(!byId.contains(999));

    std::cout << "\nAll checks passed.\n";
    return 0;
}
