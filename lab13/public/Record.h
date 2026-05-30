#pragma once
#include <cstddef>
#include <string>
#include <vector>

// ── Domain record — Variant 12: File Index ────────────────────────────
// Format: name=report.txt; size=2048; type=text; readonly=no
struct FileRecord {
    std::string name;       // file name with extension
    long long   size{};     // size in bytes (non-negative)
    std::string type;       // text / image / archive / ...
    bool        readonly{}; // yes / no
};

// ── Parse error diagnostic ────────────────────────────────────────────
struct ParseError {
    std::size_t lineNumber{};
    std::string line;
    std::string message;
};

// ── Parsing one line ──────────────────────────────────────────────────
bool parseRecord(const std::string& line,
                 FileRecord& record,
                 std::string& errorMessage);

// ── File reading ──────────────────────────────────────────────────────
bool readRecords(const std::string& path,
                 std::vector<FileRecord>& records,
                 std::vector<ParseError>& errors);
