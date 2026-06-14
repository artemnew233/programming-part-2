#include "ContainerReport.hpp"
#include <iomanip>
#include <iostream>

void printReport(const std::vector<FileRecord>& records) {
    long long total = 0;
    int       roCount = 0;
    for (const auto& r : records) { total += r.size; if (r.readonly) ++roCount; }

    std::cout << "\n=== File Catalog Report ===\n"
              << "Total files:    " << records.size() << "\n"
              << "Total size:     " << total << " bytes\n"
              << "Readonly files: " << roCount << "\n\n"
              << std::left
              << std::setw(6)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(8)  << "Ext"
              << std::setw(12) << "Size"
              << "RO\n"
              << std::string(50, '-') << "\n";

    for (const auto& r : records)
        std::cout << std::left
                  << std::setw(6)  << r.id
                  << std::setw(20) << r.name
                  << std::setw(8)  << r.extension
                  << std::setw(12) << r.size
                  << (r.readonly ? "yes" : "no") << "\n";
}
