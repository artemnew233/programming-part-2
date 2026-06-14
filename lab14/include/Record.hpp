#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>

// ── Helper types for smart-pointer experiments (variant 12) ────────────
// shared_ptr field: extension info
struct ExtensionInfo {
    std::string ext;         // e.g. ".txt"
    std::string description; // e.g. "plain text"
};

// unique_ptr field: size metadata
struct SizeMetadata {
    long long   bytes{};
    std::string humanReadable; // e.g. "2 KB"
};

// ── Basic record (no smart pointers) ─────────────────────────────────
struct FileRecord {
    int         id{};
    std::string name;
    std::string extension; // ".txt", ".png", ...
    long long   size{};    // bytes
    bool        readonly{};

    FileRecord() = default;
    FileRecord(int id, std::string name, std::string ext,
               long long size, bool ro)
        : id(id), name(std::move(name)), extension(std::move(ext)),
          size(size), readonly(ro) {}

    void print() const {
        std::cout << id << ": " << name << extension
                  << " (" << size << "b)"
                  << (readonly ? " [RO]" : "") << '\n';
    }
};

// ── Record with shared_ptr (extension field) ──────────────────────────
struct FileRecordShared {
    int         id{};
    std::string name;
    std::shared_ptr<ExtensionInfo> extension; // shared — many files share type info
    long long   size{};
    bool        readonly{};

    FileRecordShared() = default;
    FileRecordShared(int id, std::string name,
                     std::shared_ptr<ExtensionInfo> ext,
                     long long size, bool ro)
        : id(id), name(std::move(name)), extension(std::move(ext)),
          size(size), readonly(ro) {}
};

// ── Record with unique_ptr (size metadata field) ───────────────────────
struct FileRecordUnique {
    int         id{};
    std::string name;
    std::string extension;
    std::unique_ptr<SizeMetadata> sizeMeta; // exclusively owned

    // Delete copy — unique_ptr is not copyable
    FileRecordUnique(const FileRecordUnique&)            = delete;
    FileRecordUnique& operator=(const FileRecordUnique&) = delete;
    FileRecordUnique(FileRecordUnique&&)                 noexcept = default;
    FileRecordUnique& operator=(FileRecordUnique&&)      noexcept = default;

    FileRecordUnique() = default;
    FileRecordUnique(int id, std::string name, std::string ext,
                     std::unique_ptr<SizeMetadata> meta)
        : id(id), name(std::move(name)), extension(std::move(ext)),
          sizeMeta(std::move(meta)) {}
};

// ── Factory helpers ───────────────────────────────────────────────────
FileRecord      makeFileRecord(int id);
FileRecordShared makeFileRecordShared(int id,
                                      std::shared_ptr<ExtensionInfo> ext);
FileRecordUnique makeFileRecordUnique(int id);
