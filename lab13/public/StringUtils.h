#pragma once
#include <string>
#include <string_view>
#include <vector>

// ── Owning versions (std::string) ─────────────────────────────────────
std::string              trim(const std::string& text);
std::vector<std::string> split(const std::string& text, char delimiter);
bool parseKeyValue(const std::string& text,
                   std::string& key, std::string& value);

bool parseInt(const std::string& text, int& value);
bool parseLongLong(const std::string& text, long long& value);

// ── Zero-copy versions (std::string_view) ─────────────────────────────
// These views point into the original string — do NOT store them beyond
// the lifetime of the source buffer.
std::string_view              trim_view(std::string_view sv);
std::vector<std::string_view> split_view(std::string_view text, char delimiter);
bool parseKeyValueView(std::string_view part,
                       std::string_view& key, std::string_view& value);
