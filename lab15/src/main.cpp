#include "Algorithms.hpp"
#include "Record.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

static void printRecord(const FileRecord& r) {
    std::cout << std::left
              << std::setw(5)  << r.id
              << std::setw(15) << r.name
              << std::setw(7)  << r.extension
              << std::setw(12) << r.size
              << (r.readonly ? "RO" : "rw") << '\n';
}

static void printHeader() {
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(15) << "Name"
              << std::setw(7)  << "Ext"
              << std::setw(12) << "Size"
              << "RO\n"
              << std::string(42, '-') << '\n';
}

static void printVec(const std::vector<FileRecord>& v, int limit = 5) {
    printHeader();
    int n = 0;
    for (const auto& r : v) { printRecord(r); if (++n == limit) break; }
    if ((int)v.size() > limit)
        std::cout << "  ... (" << v.size() - limit << " more)\n";
}

int main() {
    auto files = generateRecords(20);

    std::cout << "=== Initial dataset (20 records) ===\n";
    printVec(files, 5);

    // ── Non-modifying ─────────────────────────────────────────────────
    std::cout << "\n=== Non-modifying algorithms ===\n";
    std::cout << "totalSize:      " << totalSize(files) << " bytes\n";
    std::cout << "count .txt:     " << countByExt(files, ".txt") << "\n";
    std::cout << "anyReadonly:    " << (anyReadonly(files) ? "yes" : "no") << "\n";
    std::cout << "allPositive:    " << (allPositiveSize(files) ? "yes" : "no") << "\n";

    auto* found = findById(files, 7);
    if (found) { std::cout << "findById(7):    "; printRecord(*found); }

    auto* largest = findLargest(files);
    if (largest) { std::cout << "findLargest:    "; printRecord(*largest); }

    // ── Modifying ─────────────────────────────────────────────────────
    std::cout << "\n=== Filtering (copy_if) ===\n";
    auto txtFiles = filterByExt(files, ".txt");
    std::cout << ".txt count: " << txtFiles.size() << "\n";
    printVec(txtFiles, 3);

    std::cout << "\n=== Readonly files (copy_if) ===\n";
    auto ro = filterReadonly(files);
    std::cout << "readonly count: " << ro.size() << "\n";
    printVec(ro, 3);

    std::cout << "\n=== Extract names (transform) ===\n";
    auto names = extractNames(files);
    for (std::size_t i = 0; i < std::min(names.size(), (std::size_t)5); ++i)
        std::cout << "  " << names[i] << "\n";

    // ── Sorting ───────────────────────────────────────────────────────
    std::cout << "\n=== Sort by size descending ===\n";
    auto sorted = files;
    sortBySizeDesc(sorted);
    printVec(sorted, 5);

    std::cout << "\n=== Sort by extension, then size desc (custom comparator) ===\n";
    auto sorted2 = files;
    std::sort(sorted2.begin(), sorted2.end(), makeExtThenSizeCmp());
    printVec(sorted2, 8);

    // ── Partitioning ──────────────────────────────────────────────────
    std::cout << "\n=== Partition by readonly (partition_copy) ===\n";
    auto [roFiles, rwFiles] = partitionByReadonly(files);
    std::cout << "readonly: " << roFiles.size()
              << " | writable: " << rwFiles.size() << "\n";

    // ── Mutation ──────────────────────────────────────────────────────
    std::cout << "\n=== scaleSize x2 (for_each) ===\n";
    auto scaled = files;
    scaleSize(scaled, 2.0);
    std::cout << "Before: " << totalSize(files)  << " bytes\n";
    std::cout << "After:  " << totalSize(scaled) << " bytes\n";

    // ── Duplicates ────────────────────────────────────────────────────
    std::cout << "\n=== removeDuplicateIds (sort + unique) ===\n";
    auto withDups = files;
    withDups.push_back(files[0]);
    withDups.push_back(files[1]);
    std::cout << "Before: " << withDups.size() << " records\n";
    withDups = removeDuplicateIds(std::move(withDups));
    std::cout << "After:  " << withDups.size() << " records\n";

    // ── Set operations ────────────────────────────────────────────────
    std::cout << "\n=== Set operations on IDs ===\n";
    auto ids1 = collectIds(files);                        // all 20
    auto subset = generateRecords(10, 99);               // different seed
    auto ids2   = collectIds(subset);

    auto common = intersectIds(ids1, ids2);
    auto diff   = differenceIds(ids1, ids2);
    std::cout << "Set A (20 ids), Set B (10 ids)\n";
    std::cout << "Intersection size: " << common.size() << "\n";
    std::cout << "Difference size:   " << diff.size()   << "\n";

    return 0;
}
