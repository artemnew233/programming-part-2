#pragma once
#include <string>
#include <vector>

// ── Domain record — Variant 12: File Catalog ──────────────────────────
// Fields: id, name, extension, size, readonly
struct FileRecord {
    int         id{};
    std::string name;
    std::string extension; // ".txt", ".png", ...
    long long   size{};    // bytes
    bool        readonly{};
};

// ── Factory / generation ──────────────────────────────────────────────
FileRecord              makeFileRecord(int id);
std::vector<FileRecord> generateRecords(std::size_t n, unsigned seed = 42);
