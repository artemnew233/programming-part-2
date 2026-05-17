#include <fstream>
#include <iomanip>
#include <iostream>

int main() {
    std::ofstream f("report.txt");
    if (!f) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    f << std::left
      << std::setw(5)  << "No"
      << std::setw(15) << "Product"
      << std::setw(10) << "Qty"
      << std::setw(12) << "Price"
      << "\n";
    f << std::string(42, '-') << "\n";

    struct Item { int id; const char* name; int qty; double price; };
    Item items[] = {
        {1, "Apple",   100, 0.99},
        {2, "Banana",  150, 0.49},
        {3, "Cherry",   50, 2.49},
        {4, "Date",     30, 5.99},
        {5, "Elderberry", 20, 8.99},
    };

    for (auto& item : items) {
        f << std::left
          << std::setw(5)  << item.id
          << std::setw(15) << item.name
          << std::setw(10) << item.qty
          << std::fixed << std::setprecision(2)
          << std::setw(12) << item.price
          << "\n";
    }

    f.close();
    std::cout << "report.txt written successfully.\n";
    return 0;
}
