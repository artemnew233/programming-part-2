#include "Record.hpp"
#include <cstdlib>

static const char* EXTENSIONS[] = {".txt",".png",".jpg",".zip",".pdf",".csv"};
static const int   EXT_COUNT    = 6;

FileRecord makeFileRecord(int id) {
    return FileRecord{
        id,
        "file_" + std::to_string(id),
        EXTENSIONS[id % EXT_COUNT],
        (long long)(id * 512 + 256),
        (id % 5 == 0)
    };
}

std::vector<FileRecord> generateRecords(std::size_t n, unsigned seed) {
    std::srand(seed);
    std::vector<FileRecord> v;
    v.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        int id = static_cast<int>(i + 1);
        FileRecord r;
        r.id        = id;
        r.name      = "file_" + std::to_string(id);
        r.extension = EXTENSIONS[std::rand() % EXT_COUNT];
        r.size      = (long long)(std::rand() % 1000000 + 100);
        r.readonly  = (std::rand() % 4 == 0); // ~25% readonly
        v.push_back(r);
    }
    return v;
}
