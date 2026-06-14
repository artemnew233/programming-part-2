#pragma once
#include "Record.hpp"
#include <array>
#include <chrono>
#include <deque>
#include <string>
#include <vector>

// ── Timing helper ─────────────────────────────────────────────────────
struct Measurement { std::string name; long long us{}; };

template <typename Fn>
Measurement measure(const std::string& name, Fn fn) {
    const auto t0 = std::chrono::steady_clock::now();
    fn();
    const auto t1 = std::chrono::steady_clock::now();
    return { name, std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count() };
}

// ── Container sizes ───────────────────────────────────────────────────
constexpr std::size_t ARRAY_SIZE  = 1000;
constexpr std::size_t LARGE_COUNT = 1000;

// ── Fill helpers ──────────────────────────────────────────────────────
std::array<FileRecord, ARRAY_SIZE> makeArray();
std::vector<FileRecord>            makeVector(std::size_t n = LARGE_COUNT);
std::deque<FileRecord>             makeDeque (std::size_t n = LARGE_COUNT);

// ── Operations ────────────────────────────────────────────────────────
// Search (no <algorithm>)
const FileRecord* findLargeVector(const std::vector<FileRecord>& v, long long threshold);
const FileRecord* findLargeDeque (const std::deque<FileRecord>&  d, long long threshold);

// Count by extension (no <algorithm>)
int countByExtVector(const std::vector<FileRecord>& v, const std::string& ext);
int countByExtDeque (const std::deque<FileRecord>&  d, const std::string& ext);
int countByExtArray (const std::array<FileRecord, ARRAY_SIZE>& a, const std::string& ext);

// Build new sequence (no <algorithm>)
std::vector<FileRecord> filterReadonlyVector(const std::vector<FileRecord>& v);

// Timing experiments
void runTimingExperiments();

// Smart-pointer experiments
void smartPointerExperiments();

// Capacity / invalidation demo
void vectorCapacityDemo();
