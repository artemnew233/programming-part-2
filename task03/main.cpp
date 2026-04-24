#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::left
              << std::setw(5)  << "No"
              << std::setw(15) << "Name"
              << std::setw(10) << "Score"
              << std::setw(10) << "Average"
              << "\n";
    std::cout << std::string(40, '-') << "\n";

    struct Row { int id; const char* name; int score; double avg; };
    Row rows[] = {
        {1, "Alice",   95, 4.8},
        {2, "Bob",     78, 3.9},
        {3, "Charlie", 88, 4.4},
        {4, "Diana",   91, 4.6},
        {5, "Eve",     65, 3.2},
    };

    for (auto& r : rows) {
        std::cout << std::left
                  << std::setw(5)  << r.id
                  << std::setw(15) << r.name
                  << std::setw(10) << r.score
                  << std::fixed << std::setprecision(2)
                  << std::setw(10) << r.avg
                  << "\n";
    }
    return 0;
}
