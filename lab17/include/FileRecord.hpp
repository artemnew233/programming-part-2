#pragma once
#include <string>
#include <vector>

struct FileRecord {
    int         id{};
    std::string name;
    std::string extension;
    long long   size{};
    bool        readonly{};
};

inline std::vector<FileRecord> makeDataset() {
    return {
        { 1, "report",       ".txt",   2048, false},
        { 2, "config",       ".json",   512, true },
        { 3, "photo1",       ".jpg",  20480, false},
        { 4, "backup",       ".zip",  51200, true },
        { 5, "notes",        ".txt",    256, false},
        { 6, "log",          ".txt",   8192, false},
        { 7, "data",         ".csv",   4096, false},
        { 8, "readme",       ".txt",    512, false},
        { 9, "database",     ".db",   16384, false},
        {10, "photo2",       ".jpg",  30720, true },
        {11, "script",       ".py",    1024, false},
        {12, "archive",      ".tar", 102400, true },
        {13, "index",        ".html",  2048, false},
        {14, "styles",       ".css",    768, false},
        {15, "fonts",        ".ttf",   3072, true },
        {16, "icon",         ".ico",    256, true },
        {17, "manifest",     ".json",   128, false},
        {18, "credentials",  ".json",    64, true },
        {19, "output",       ".csv",   8192, false},
        {20, "video",        ".mp4", 204800, false},
        {21, "thumbnail",    ".jpg",   5120, false},
        {22, "settings",     ".json",   256, true },
        {23, "export",       ".csv",  16384, false},
        {24, "presentation", ".pptx", 40960, false},
        {25, "spreadsheet",  ".xlsx", 20480, false},
    };
}
