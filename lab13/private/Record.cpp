#include "Record.h"
#include "StringUtils.h"
#include <fstream>
#include <map>

bool parseRecord(const std::string& line,
                 FileRecord& record,
                 std::string& errorMessage) {
    // Use zero-copy split/parse; convert to string only when storing i think
    const auto parts = split_view(line, ';');
    std::map<std::string, std::string> fields;

    for (const auto part : parts) {
        std::string_view key, value;
        if (!parseKeyValueView(part, key, value)) {
            errorMessage = "invalid key=value pair";
            return false;
        }
        fields[std::string(key)] = std::string(value);
    }

    // Required fields
    for (const auto& req : {"name", "size", "type", "readonly"}) {
        if (fields.find(req) == fields.end()) {
            errorMessage = std::string("missing required field: ") + req;
            return false;
        }
    }

    // name — must be non-empty and contain a dot for good measures (extension or msth like that)
    record.name = fields["name"];
    if (record.name.empty()) {
        errorMessage = "name is empty";
        return false;
    }
    if (record.name.find('.') == std::string::npos) {
        errorMessage = "name has no extension";
        return false;
    }

    // size — non-negative int integer
    if (!parseLongLong(fields["size"], record.size) || record.size < 0) {
        errorMessage = "size is not a valid non-negative number";
        return false;
    }

    // type — any non-empty string will work
    record.type = fields["type"];
    if (record.type.empty()) {
        errorMessage = "type is empty";
        return false;
    }

    // readonly — yes / no 
    const auto& ro = fields["readonly"];
    if (ro == "yes")       record.readonly = true;
    else if (ro == "no")   record.readonly = false;
    else {
        errorMessage = "readonly must be yes or no";
        return false;
    }

    return true;
}

bool readRecords(const std::string& path,
                 std::vector<FileRecord>& records,
                 std::vector<ParseError>& errors) {
    std::ifstream file(path);
    if (!file) return false;

    std::string line;
    std::size_t lineNum = 0;
    while (std::getline(file, line)) {
        ++lineNum;
        if (trim(line).empty()) continue;

        FileRecord rec;
        std::string err;
        if (parseRecord(line, rec, err))
            records.push_back(rec);
        else
            errors.push_back({lineNum, line, err});
    }
    return true;
}
