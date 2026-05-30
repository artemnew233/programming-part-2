#pragma once
#include "Record.hpp"
#include <functional>
#include <string>
#include <vector>

// ── Non-modifying ─────────────────────────────────────────────────────
long long   totalSize(const std::vector<FileRecord>& v);
int         countByExt(const std::vector<FileRecord>& v, const std::string& ext);
bool        anyReadonly(const std::vector<FileRecord>& v);
bool        allPositiveSize(const std::vector<FileRecord>& v);
const FileRecord* findById(const std::vector<FileRecord>& v, int id);
const FileRecord* findLargest(const std::vector<FileRecord>& v);

// ── Modifying ─────────────────────────────────────────────────────────
std::vector<FileRecord> filterByExt(const std::vector<FileRecord>& v,
                                     const std::string& ext);
std::vector<FileRecord> filterReadonly(const std::vector<FileRecord>& v);
std::vector<std::string> extractNames(const std::vector<FileRecord>& v);
void                     scaleSize(std::vector<FileRecord>& v, double factor);
void                     markAllReadonly(std::vector<FileRecord>& v);
std::vector<FileRecord>  removeDuplicateIds(std::vector<FileRecord> v);

// ── Sorting (six comparators) ─────────────────────────────────────────
void sortById       (std::vector<FileRecord>& v);
void sortByName     (std::vector<FileRecord>& v);
void sortBySizeAsc  (std::vector<FileRecord>& v);
void sortBySizeDesc (std::vector<FileRecord>& v);
void sortByExt      (std::vector<FileRecord>& v);
void sortByReadonly (std::vector<FileRecord>& v);

// ── Partitioning ──────────────────────────────────────────────────────
// Splits into {readonly, writable}
std::pair<std::vector<FileRecord>, std::vector<FileRecord>>
    partitionByReadonly(const std::vector<FileRecord>& v);

// ── Lambda / functor comparison ───────────────────────────────────────
// Returns a comparator that sorts by extension, then by size descending
std::function<bool(const FileRecord&, const FileRecord&)> makeExtThenSizeCmp();

// ── Set-like operations (on sorted vectors) ───────────────────────────
std::vector<int> collectIds(const std::vector<FileRecord>& v);  // sorted id list
std::vector<int> intersectIds(std::vector<int> a, std::vector<int> b);
std::vector<int> differenceIds(std::vector<int> a, std::vector<int> b);
