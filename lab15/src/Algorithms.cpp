#include "Algorithms.hpp"
#include <algorithm>
#include <numeric>

// ── Non-modifying ─────────────────────────────────────────────────────

long long totalSize(const std::vector<FileRecord>& v) {
    return std::accumulate(v.begin(), v.end(), 0LL,
        [](long long acc, const FileRecord& r) { return acc + r.size; });
}

int countByExt(const std::vector<FileRecord>& v, const std::string& ext) {
    return static_cast<int>(
        std::count_if(v.begin(), v.end(),
            [&ext](const FileRecord& r) { return r.extension == ext; }));
}

bool anyReadonly(const std::vector<FileRecord>& v) {
    return std::any_of(v.begin(), v.end(),
        [](const FileRecord& r) { return r.readonly; });
}

bool allPositiveSize(const std::vector<FileRecord>& v) {
    return std::all_of(v.begin(), v.end(),
        [](const FileRecord& r) { return r.size > 0; });
}

const FileRecord* findById(const std::vector<FileRecord>& v, int id) {
    auto it = std::find_if(v.begin(), v.end(),
        [id](const FileRecord& r) { return r.id == id; });
    return it == v.end() ? nullptr : &*it;
}

const FileRecord* findLargest(const std::vector<FileRecord>& v) {
    if (v.empty()) return nullptr;
    auto it = std::max_element(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.size < b.size; });
    return &*it;
}

// ── Modifying ─────────────────────────────────────────────────────────

std::vector<FileRecord> filterByExt(const std::vector<FileRecord>& v,
                                     const std::string& ext) {
    std::vector<FileRecord> out;
    std::copy_if(v.begin(), v.end(), std::back_inserter(out),
        [&ext](const FileRecord& r) { return r.extension == ext; });
    return out;
}

std::vector<FileRecord> filterReadonly(const std::vector<FileRecord>& v) {
    std::vector<FileRecord> out;
    std::copy_if(v.begin(), v.end(), std::back_inserter(out),
        [](const FileRecord& r) { return r.readonly; });
    return out;
}

std::vector<std::string> extractNames(const std::vector<FileRecord>& v) {
    std::vector<std::string> names(v.size());
    std::transform(v.begin(), v.end(), names.begin(),
        [](const FileRecord& r) { return r.name + r.extension; });
    return names;
}

void scaleSize(std::vector<FileRecord>& v, double factor) {
    std::for_each(v.begin(), v.end(),
        [factor](FileRecord& r) {
            r.size = static_cast<long long>(r.size * factor);
        });
}

void markAllReadonly(std::vector<FileRecord>& v) {
    std::for_each(v.begin(), v.end(),
        [](FileRecord& r) { r.readonly = true; });
}

std::vector<FileRecord> removeDuplicateIds(std::vector<FileRecord> v) {
    // sort by id, then unique-erase consecutive duplicates
    std::sort(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.id < b.id; });
    v.erase(
        std::unique(v.begin(), v.end(),
            [](const FileRecord& a, const FileRecord& b) { return a.id == b.id; }),
        v.end());
    return v;
}

// ── Sorting ───────────────────────────────────────────────────────────

void sortById(std::vector<FileRecord>& v) {
    std::sort(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.id < b.id; });
}

void sortByName(std::vector<FileRecord>& v) {
    std::sort(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.name < b.name; });
}

void sortBySizeAsc(std::vector<FileRecord>& v) {
    std::sort(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.size < b.size; });
}

void sortBySizeDesc(std::vector<FileRecord>& v) {
    std::sort(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.size > b.size; });
}

void sortByExt(std::vector<FileRecord>& v) {
    std::stable_sort(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) {
            return a.extension < b.extension;
        });
}

void sortByReadonly(std::vector<FileRecord>& v) {
    // readonly=true first
    std::stable_sort(v.begin(), v.end(),
        [](const FileRecord& a, const FileRecord& b) {
            return static_cast<int>(b.readonly) < static_cast<int>(a.readonly);
        });
}

// ── Partitioning ──────────────────────────────────────────────────────

std::pair<std::vector<FileRecord>, std::vector<FileRecord>>
    partitionByReadonly(const std::vector<FileRecord>& v) {
    std::vector<FileRecord> ro, rw;
    // std::partition_copy splits one range into two based on a predicate
    std::partition_copy(v.begin(), v.end(),
        std::back_inserter(ro), std::back_inserter(rw),
        [](const FileRecord& r) { return r.readonly; });
    return {ro, rw};
}

// ── Lambda / functor comparator ───────────────────────────────────────

std::function<bool(const FileRecord&, const FileRecord&)> makeExtThenSizeCmp() {
    return [](const FileRecord& a, const FileRecord& b) {
        if (a.extension != b.extension) return a.extension < b.extension;
        return a.size > b.size;  // larger first within same extension
    };
}

// ── Set-like operations ───────────────────────────────────────────────

std::vector<int> collectIds(const std::vector<FileRecord>& v) {
    std::vector<int> ids(v.size());
    std::transform(v.begin(), v.end(), ids.begin(),
        [](const FileRecord& r) { return r.id; });
    std::sort(ids.begin(), ids.end());
    return ids;
}

std::vector<int> intersectIds(std::vector<int> a, std::vector<int> b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::vector<int> out;
    std::set_intersection(a.begin(), a.end(),
                          b.begin(), b.end(),
                          std::back_inserter(out));
    return out;
}

std::vector<int> differenceIds(std::vector<int> a, std::vector<int> b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::vector<int> out;
    std::set_difference(a.begin(), a.end(),
                        b.begin(), b.end(),
                        std::back_inserter(out));
    return out;
}
