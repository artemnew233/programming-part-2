#include "ContainerExperiments.hpp"
#include "ContainerReport.hpp"
#include "Record.hpp"

#include <array>
#include <deque>
#include <iostream>
#include <vector>

int main() {
    // ── Fill three containers ─────────────────────────────────────────
    auto arr = makeArray();
    auto vec = makeVector();
    auto deq = makeDeque();

    // ── Indexed access (array + vector + deque) ───────────────────────
    std::cout << "=== Indexed access ===\n";
    std::cout << "arr[0]:  "; arr[0].print();
    std::cout << "vec[0]:  "; vec[0].print();
    std::cout << "deq[0]:  "; deq[0].print();
    std::cout << "vec.at(5): "; vec.at(5).print();

    // ── Range-for traversal ───────────────────────────────────────────
    std::cout << "\n=== Range-for (first 3 of each) ===\n";
    int n = 0;
    for (const auto& r : vec) { r.print(); if (++n == 3) break; }

    // ── Explicit iterator traversal ───────────────────────────────────
    std::cout << "\n=== Explicit iterator (deque, first 3) ===\n";
    n = 0;
    for (auto it = deq.begin(); it != deq.end() && n < 3; ++it, ++n)
        it->print();

    // ── front() / back() ──────────────────────────────────────────────
    std::cout << "\n=== front() / back() ===\n";
    std::cout << "vec front: "; vec.front().print();
    std::cout << "vec back:  "; vec.back().print();
    std::cout << "deq front: "; deq.front().print();

    // ── Insertion at end ──────────────────────────────────────────────
    std::cout << "\n=== Insertion at end ===\n";
    vec.push_back(makeFileRecord(9001));
    deq.push_back(makeFileRecord(9001));
    std::cout << "vec size after push_back: " << vec.size() << "\n";

    // ── Insertion at beginning ────────────────────────────────────────
    std::cout << "\n=== Insertion at beginning ===\n";
    // vector: O(n) — must shift everything
    vec.insert(vec.begin(), makeFileRecord(9002));
    // deque: O(1) — efficient
    deq.push_front(makeFileRecord(9002));
    std::cout << "vec[0] after insert: "; vec[0].print();
    std::cout << "deq[0] after push_front: "; deq[0].print();

    // ── Insertion in the middle ───────────────────────────────────────
    std::cout << "\n=== Insertion in the middle ===\n";
    auto midVec = vec.begin() + (long)(vec.size() / 2);
    vec.insert(midVec, makeFileRecord(9003));
    auto midDeq = deq.begin() + (long)(deq.size() / 2);
    deq.insert(midDeq, makeFileRecord(9003));

    // ── Deletion ──────────────────────────────────────────────────────
    std::cout << "\n=== Deletion ===\n";
    vec.erase(vec.begin());
    deq.pop_front();
    std::cout << "vec size after erase: " << vec.size() << "\n";
    std::cout << "deq size after pop_front: " << deq.size() << "\n";

    // ── Search (no <algorithm>) ───────────────────────────────────────
    std::cout << "\n=== Search — first file > 200KB ===\n";
    auto* found = findLargeVector(vec, 200000);
    if (found) { std::cout << "vector: "; found->print(); }
    else std::cout << "vector: not found\n";

    // ── Count (no <algorithm>) ────────────────────────────────────────
    std::cout << "\n=== Count .txt files ===\n";
    std::cout << "vector: " << countByExtVector(vec, ".txt") << "\n";
    std::cout << "deque:  " << countByExtDeque(deq, ".txt")  << "\n";
    std::cout << "array:  " << countByExtArray(arr, ".txt")  << "\n";

    // ── Filter (build new sequence, no <algorithm>) ───────────────────
    std::cout << "\n=== Readonly files ===\n";
    auto ro = filterReadonlyVector(vec);
    std::cout << "readonly count: " << ro.size() << "\n";

    // ── Report for first 10 ───────────────────────────────────────────
    std::vector<FileRecord> first10(vec.begin(),
                                     vec.begin() + std::min((std::size_t)10, vec.size()));
    printReport(first10);

    // ── Experiments ───────────────────────────────────────────────────
    runTimingExperiments();
    smartPointerExperiments();
    vectorCapacityDemo();

    return 0;
}
