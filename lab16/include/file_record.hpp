#pragma once
#include <iostream>
#include <string>

struct FileRecord {
    int         id{};
    std::string name;
    std::string extension;
    long long   size{};
    bool        readonly{};

    void print() const {
        std::cout << id << " " << name << extension
                  << " " << size << "b"
                  << (readonly ? " [RO]" : "") << '\n';
    }
};
