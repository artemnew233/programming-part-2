#include "Record.h"
#include "ReportBuilder.h"
#include "StringUtils.h"

#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::vector<FileRecord> records;
    std::vector<ParseError> errors;

    if (!readRecords("data/input.txt", records, errors)) {
        std::cerr << "Cannot open data/input.txt\n";
        return 1;
    }

    std::cout << "Read " << records.size() << " valid records, "
              << errors.size() << " invalid.\n\n";

    const std::string report = buildReport(records, errors);

    // print to console
    std::cout << report;

    // write to file
    std::ofstream out("data/report.txt");
    if (!out)
        std::cerr << "Cannot write report.txt\n";
    else
        out << report;

    return 0;
}
