#pragma once
#include "Record.h"
#include <string>
#include <vector>

std::string buildReport(const std::vector<FileRecord>& records,
                        const std::vector<ParseError>& errors);

// regex helpers
std::string normalizeSpaces(const std::string& text);
bool        validateFileName(const std::string& name);  // must have extension
std::string maskLargeIds(const std::string& text);      // replace long numeric ids
