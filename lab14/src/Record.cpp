#include "Record.hpp"

static const char* EXTENSIONS[] = {".txt",".png",".jpg",".zip",".pdf",".csv"};
static const int   EXT_COUNT    = 6;

FileRecord makeFileRecord(int id) {
    const std::string ext = EXTENSIONS[id % EXT_COUNT];
    return FileRecord{
        id,
        "file_" + std::to_string(id),
        ext,
        (long long)(id * 512 + 256),
        (id % 5 == 0)
    };
}

FileRecordShared makeFileRecordShared(int id,
                                      std::shared_ptr<ExtensionInfo> ext) {
    return FileRecordShared{
        id,
        "file_" + std::to_string(id),
        std::move(ext),
        (long long)(id * 512 + 256),
        (id % 5 == 0)
    };
}

FileRecordUnique makeFileRecordUnique(int id) {
    auto meta = std::make_unique<SizeMetadata>();
    meta->bytes        = (long long)(id * 512 + 256);
    meta->humanReadable = std::to_string(meta->bytes / 1024) + " KB";
    return FileRecordUnique{
        id,
        "file_" + std::to_string(id),
        ".txt",
        std::move(meta)
    };
}
