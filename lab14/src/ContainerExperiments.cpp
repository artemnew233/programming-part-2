#include "ContainerExperiments.hpp"
#include <iostream>
#include <utility>

// ── Fill helpers ──────────────────────────────────────────────────────
std::array<FileRecord, ARRAY_SIZE> makeArray() {
    std::array<FileRecord, ARRAY_SIZE> a;
    for (std::size_t i = 0; i < ARRAY_SIZE; ++i)
        a[i] = makeFileRecord(static_cast<int>(i + 1));
    return a;
}

std::vector<FileRecord> makeVector(std::size_t n) {
    std::vector<FileRecord> v;
    v.reserve(n);
    for (std::size_t i = 0; i < n; ++i)
        v.push_back(makeFileRecord(static_cast<int>(i + 1)));
    return v;
}

std::deque<FileRecord> makeDeque(std::size_t n) {
    std::deque<FileRecord> d;
    for (std::size_t i = 0; i < n; ++i)
        d.push_back(makeFileRecord(static_cast<int>(i + 1)));
    return d;
}

// ── Search (no <algorithm>) ───────────────────────────────────────────
const FileRecord* findLargeVector(const std::vector<FileRecord>& v,
                                   long long threshold) {
    for (const auto& r : v)
        if (r.size > threshold) return &r;
    return nullptr;
}

const FileRecord* findLargeDeque(const std::deque<FileRecord>& d,
                                  long long threshold) {
    for (const auto& r : d)
        if (r.size > threshold) return &r;
    return nullptr;
}

// ── Count by extension (no <algorithm>) ──────────────────────────────
int countByExtVector(const std::vector<FileRecord>& v, const std::string& ext) {
    int n = 0;
    for (const auto& r : v) if (r.extension == ext) ++n;
    return n;
}

int countByExtDeque(const std::deque<FileRecord>& d, const std::string& ext) {
    int n = 0;
    for (const auto& r : d) if (r.extension == ext) ++n;
    return n;
}

int countByExtArray(const std::array<FileRecord, ARRAY_SIZE>& a,
                    const std::string& ext) {
    int n = 0;
    for (const auto& r : a) if (r.extension == ext) ++n;
    return n;
}

// ── Filter readonly ───────────────────────────────────────────────────
std::vector<FileRecord> filterReadonlyVector(const std::vector<FileRecord>& v) {
    std::vector<FileRecord> out;
    for (const auto& r : v)
        if (r.readonly) out.push_back(r);
    return out;
}

// ── Timing experiments ────────────────────────────────────────────────
void runTimingExperiments() {
    std::cout << "\n=== Timing Experiments (N=" << LARGE_COUNT << ") ===\n";

    auto mVecFill  = measure("vector fill",  []{ auto v = makeVector(); (void)v; });
    auto mDeqFill  = measure("deque  fill",  []{ auto d = makeDeque();  (void)d; });

    auto vec = makeVector();
    auto deq = makeDeque();
    auto arr = makeArray();

    auto mVecTrav  = measure("vector traversal", [&]{
        long long s=0; for(const auto& r:vec) s+=r.size; (void)s;
    });
    auto mDeqTrav  = measure("deque  traversal", [&]{
        long long s=0; for(const auto& r:deq) s+=r.size; (void)s;
    });
    auto mArrTrav  = measure("array  traversal", [&]{
        long long s=0; for(const auto& r:arr) s+=r.size; (void)s;
    });

    auto mVecFront = measure("vector push_front (erase+insert)", [&]{
        vec.insert(vec.begin(), makeFileRecord(9999));
        vec.erase(vec.begin());
    });
    auto mDeqFront = measure("deque  push_front", [&]{
        deq.push_front(makeFileRecord(9999));
        deq.pop_front();
    });

    auto mVecMid   = measure("vector insert middle", [&]{
        auto it = vec.begin() + (long)(vec.size()/2);
        vec.insert(it, makeFileRecord(8888));
    });
    auto mDeqMid   = measure("deque  insert middle", [&]{
        auto it = deq.begin() + (long)(deq.size()/2);
        deq.insert(it, makeFileRecord(8888));
    });

    for (const auto& m : {mVecFill,mDeqFill,
                           mVecTrav,mDeqTrav,mArrTrav,
                           mVecFront,mDeqFront,
                           mVecMid,mDeqMid})
        std::cout << "  " << m.name << ": " << m.us << " us\n";
}

// ── Smart-pointer experiments ─────────────────────────────────────────
void smartPointerExperiments() {
    std::cout << "\n=== Shared-ptr experiment (extension field) ===\n";
    auto txtInfo = std::make_shared<ExtensionInfo>(ExtensionInfo{".txt","plain text"});

    std::vector<FileRecordShared> vs;
    vs.reserve(4);

    // push_back with ready object
    FileRecordShared r1 = makeFileRecordShared(1, txtInfo);
    vs.push_back(std::move(r1));

    // emplace_back — construct in place
    vs.emplace_back(2, "file_2", txtInfo, 1024, false);
    vs.emplace_back(3, "file_3", txtInfo, 2048, true);

    std::cout << "  txtInfo use_count: " << txtInfo.use_count()
              << " (1 local + " << vs.size() << " in vector = "
              << 1 + (int)vs.size() << ")\n";

    std::cout << "\n=== Unique-ptr experiment (size metadata field) ===\n";
    std::vector<FileRecordUnique> vu;
    vu.reserve(3);

    // push_back(std::move(ready)) — must move, copy is deleted
    FileRecordUnique u1 = makeFileRecordUnique(1);
    vu.push_back(std::move(u1));

    // emplace_back — construct in container
    vu.emplace_back(2, "file_2", ".png",
                    std::make_unique<SizeMetadata>(SizeMetadata{10240,"10 KB"}));
    vu.emplace_back(3, "file_3", ".zip",
                    std::make_unique<SizeMetadata>(SizeMetadata{51200,"50 KB"}));

    // push_back(ready)  <- would not compile (deleted copy)
    // push_back(vu[0]); // ERROR: use of deleted copy constructor

    for (const auto& r : vu)
        std::cout << "  " << r.id << " " << r.name
                  << " " << (r.sizeMeta ? r.sizeMeta->humanReadable : "?") << '\n';
}

// ── Capacity / iterator invalidation demo ────────────────────────────
void vectorCapacityDemo() {
    std::cout << "\n=== vector capacity & iterator invalidation ===\n";
    std::vector<FileRecord> v;
    v.reserve(2);
    v.push_back(makeFileRecord(1));
    v.push_back(makeFileRecord(2));

    const FileRecord* before = v.data();
    const std::size_t capBefore = v.capacity();

    v.push_back(makeFileRecord(3)); // triggers reallocation

    const FileRecord* after = v.data();
    const std::size_t capAfter = v.capacity();

    std::cout << "  capacity before: " << capBefore << '\n';
    std::cout << "  capacity after:  " << capAfter  << '\n';
    std::cout << "  data moved:      " << (before != after ? "yes" : "no") << '\n';
    std::cout << "  (old pointer is now invalid — must not dereference it)\n";
}
