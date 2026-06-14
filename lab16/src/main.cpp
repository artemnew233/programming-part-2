#include "file_record.hpp"
#include "simple_forward_list.hpp"
#include "simple_vector.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>

static void demo_forward_list() {
    std::cout << "=== SimpleForwardList<FileRecord> ===\n";

    SimpleForwardList<FileRecord> list;
    list.push_front({5, "video",   ".mp4", 102400, false});
    list.push_front({4, "archive", ".zip",  51200, true});
    list.push_front({3, "photo",   ".jpg",  20480, false});
    list.push_front({2, "config",  ".json",   512, true});
    list.push_front({1, "report",  ".txt",   2048, false});

    std::cout << "range-for (non-const):\n";
    for (auto& r : list) r.print();

    const SimpleForwardList<FileRecord>& clist = list;
    std::cout << "\ncbegin/cend traversal:\n";
    for (auto it = clist.cbegin(); it != clist.cend(); ++it) it->print();

    const auto large = std::find_if(list.begin(), list.end(),
        [](const FileRecord& r) { return r.size > 10000; });
    if (large != list.end()) {
        std::cout << "\nFirst large file: ";
        large->print();
    }

    const auto roCount = std::ranges::count_if(list,
        [](const FileRecord& r) { return r.readonly; });
    std::cout << "Readonly count: " << roCount << '\n';

    auto it = list.insert_after(list.begin(),
        {6, "notes", ".md", 256, false});
    std::cout << "\nAfter insert_after(begin): ";
    it->print();

    list.erase_after(list.begin());
    std::cout << "After erase_after(begin), size=" << list.size() << '\n';

    SimpleForwardList<FileRecord> copy  = list;
    SimpleForwardList<FileRecord> moved = std::move(copy);
    std::cout << "Moved size=" << moved.size() << ", copy size=" << copy.size() << '\n';
}

static void demo_simple_vector() {
    std::cout << "\n=== SimpleVector<FileRecord> ===\n";

    SimpleVector<FileRecord> vec;
    vec.reserve(8);
    std::cout << "capacity after reserve(8): " << vec.capacity() << '\n';

    vec.push_back({1, "report",  ".txt",   2048, false});
    vec.push_back({2, "config",  ".json",   512, true});
    vec.emplace_back(FileRecord{3, "photo", ".jpg", 20480, false});
    vec.push_back({4, "archive", ".zip",  51200, true});

    std::cout << "size=" << vec.size() << " capacity=" << vec.capacity() << '\n';

    std::cout << "range-for:\n";
    for (const auto& r : vec) r.print();

    std::cout << "front: "; vec.front().print();
    std::cout << "back:  "; vec.back().print();
    std::cout << "at(2): "; vec.at(2).print();

    const auto largest = std::max_element(vec.begin(), vec.end(),
        [](const FileRecord& a, const FileRecord& b) { return a.size < b.size; });
    std::cout << "Largest: "; largest->print();

    auto new_end = std::remove_if(vec.begin(), vec.end(),
        [](const FileRecord& r) { return r.readonly; });
    vec.resize(static_cast<std::size_t>(std::distance(vec.begin(), new_end)));
    std::cout << "After removing readonly, size=" << vec.size() << '\n';

    SimpleVector<FileRecord> copy  = vec;
    SimpleVector<FileRecord> moved = std::move(vec);
    std::cout << "Moved size=" << moved.size() << " original size=" << vec.size() << '\n';
}

int main() {
    demo_forward_list();
    demo_simple_vector();
    return 0;
}
