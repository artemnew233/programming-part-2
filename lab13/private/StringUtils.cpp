#include "StringUtils.h"
#include <sstream>

// ── trim ──────────────────────────────────────────────────────────────
std::string trim(const std::string& text) {
    const std::string ws = " \t\n\r";
    const auto first = text.find_first_not_of(ws);
    if (first == std::string::npos) return {};
    const auto last = text.find_last_not_of(ws);
    return text.substr(first, last - first + 1);
}

// ── split ─────────────────────────────────────────────────────────────
std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::istringstream input(text);
    std::string part;
    while (std::getline(input, part, delimiter))
        parts.push_back(trim(part));
    return parts;
}

// ── parseKeyValue ─────────────────────────────────────────────────────
bool parseKeyValue(const std::string& text,
                   std::string& key, std::string& value) {
    const auto pos = text.find('=');
    if (pos == std::string::npos) return false;
    key   = trim(text.substr(0, pos));
    value = trim(text.substr(pos + 1));
    return !key.empty() && !value.empty();
}

// ── parseInt ──────────────────────────────────────────────────────────
bool parseInt(const std::string& text, int& value) {
    std::istringstream in(text);
    in >> value >> std::ws;
    return in && in.eof();
}

// ── parseLongLong ─────────────────────────────────────────────────────
bool parseLongLong(const std::string& text, long long& value) {
    std::istringstream in(text);
    in >> value >> std::ws;
    return in && in.eof();
}

// ── Zero-copy: trim_view ──────────────────────────────────────────────
std::string_view trim_view(std::string_view sv) {
    constexpr std::string_view ws = " \t\n\r";
    const auto first = sv.find_first_not_of(ws);
    if (first == std::string_view::npos) return {};
    sv.remove_prefix(first);
    const auto last = sv.find_last_not_of(ws);
    sv.remove_suffix(sv.size() - last - 1);
    return sv;
}

// ── Zero-copy: split_view ─────────────────────────────────────────────
std::vector<std::string_view> split_view(std::string_view text, char delimiter) {
    std::vector<std::string_view> parts;
    while (!text.empty()) {
        const auto pos = text.find(delimiter);
        if (pos == std::string_view::npos) {
            parts.push_back(trim_view(text));
            break;
        }
        parts.push_back(trim_view(text.substr(0, pos)));
        text.remove_prefix(pos + 1);
    }
    return parts;
}

// ── Zero-copy: parseKeyValueView ──────────────────────────────────────
bool parseKeyValueView(std::string_view part,
                       std::string_view& key, std::string_view& value) {
    const auto pos = part.find('=');
    if (pos == std::string_view::npos) return false;
    key   = trim_view(part.substr(0, pos));
    value = trim_view(part.substr(pos + 1));
    return !key.empty() && !value.empty();
}
