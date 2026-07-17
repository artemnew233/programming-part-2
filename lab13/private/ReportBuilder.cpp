#include "ReportBuilder.h"
#include "StringUtils.h"
#include <iomanip>
#include <map>
#include <regex>
#include <sstream>

// ── regex helpers ───────────────────────────────────────────────────── i like how this comment looks nice, will do that from now on ngl

// Normalize multiple spaces to one
std::string normalizeSpaces(const std::string& text) {
    static const std::regex multi(R"(\s{2,})");
    return std::regex_replace(text, multi, " ");
}

// Validate file name: must match pattern word.ext
bool validateFileName(const std::string& name) {
    static const std::regex pattern(R"([A-Za-z0-9_\-]+\.[A-Za-z0-9]+)");
    return std::regex_match(name, pattern);
}

// Mask long numeric ids (7+ digits) in a string
std::string maskLargeIds(const std::string& text) {
    static const std::regex idPattern(R"(\b\d{7,}\b)");
    return std::regex_replace(text, idPattern, "[id]");
}

// ── report generation ─────────────────────────────────────────────────
std::string buildReport(const std::vector<FileRecord>& records,
                        const std::vector<ParseError>& errors) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(0);

    // ── Statistics ────────────────────────────────────────────────────
    long long totalSize   = 0;
    int       readonlyCount = 0;
    const FileRecord* largest = nullptr;

    std::map<std::string, int> byType;

    for (const auto& r : records) {
        totalSize += r.size;
        if (r.readonly) ++readonlyCount;
        byType[r.type]++;
        if (!largest || r.size > largest->size) largest = &r;
    }

    // ── Header ────────────────────────────────────────────────────────
    out << "File Index Report\n"
        << "=================\n"
        << "Total lines:    " << records.size() + errors.size() << "\n"
        << "Valid records:  " << records.size() << "\n"
        << "Invalid records:" << errors.size() << "\n"
        << "Total size:     " << totalSize << " bytes\n"
        << "Readonly files: " << readonlyCount << "\n";

    if (largest)
        out << "Largest file:   " << largest->name
            << " (" << largest->size << " bytes)\n";

    // ── Type breakdown ────────────────────────────────────────────────
    out << "\nFiles by type:\n";
    for (const auto& [type, count] : byType)
        out << "  " << std::left << std::setw(12) << type << count << "\n";

    // ── Filtered table: readonly files ────────────────────────────────
    out << "\nReadonly files:\n"
        << std::left
        << std::setw(25) << "Name"
        << std::setw(12) << "Size"
        << std::setw(12) << "Type" << "\n"
        << std::string(49, '-') << "\n";

    for (const auto& r : records) {
        if (!r.readonly) continue;
        out << std::left
            << std::setw(25) << r.name
            << std::setw(12) << r.size
            << std::setw(12) << r.type << "\n";
    }

    // ── Invalid lines ─────────────────────────────────────────────────
    if (!errors.empty()) {
        out << "\nInvalid lines:\n";
        for (const auto& e : errors)
            out << "  Line " << e.lineNumber << ": " << e.message << "\n"
                << "    -> " << e.line << "\n";
    }

    // ── UTF-8 observation ─────────────────────────────────────────────
    out << "\nUTF-8 observation:\n";
    std::string ascii = "file";
    std::string utf8  = "файл"; // Ukrainian — 4 letters, 8 bytes in UTF-8
    out << "  \"" << ascii << "\": " << ascii.size() << " bytes\n";
    out << "  \"" << utf8  << "\": " << utf8.size()  << " bytes\n";

    // ── C-string / snprintf demo ──────────────────────────────────────
    out << "\nC-string / snprintf demo:\n";
    if (!records.empty()) {
        const char* rawName = records[0].name.c_str();
        char buffer[64];
        int written = std::snprintf(buffer, sizeof(buffer),
                                    "name=%s; size=%lld",
                                    rawName, records[0].size);
        if (written < 0 || static_cast<std::size_t>(written) >= sizeof(buffer))
            out << "  [buffer too small]\n";
        else
            out << "  " << buffer << "\n";
    }

    // ── Regex replacement demo ────────────────────────────────────────
    out << "\nRegex demos:\n";
    std::string messy = "report   backup   archive";
    out << "  normalizeSpaces: \"" << normalizeSpaces(messy) << "\"\n";
    std::string withId = "file_1234567_backup.zip";
    out << "  maskLargeIds:    \"" << maskLargeIds(withId) << "\"\n";

    out << "\n[report end]\n";
    return out.str();
}
