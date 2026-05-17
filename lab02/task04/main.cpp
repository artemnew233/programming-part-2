#include <iostream>
#include <iomanip>

int main() {
    double val = 123456.789;

    std::cout << "Default:          " << val << "\n";
    std::cout << "Fixed:            " << std::fixed << val << "\n";
    std::cout << "Scientific:       " << std::scientific << val << "\n";
    std::cout << "Fixed 2 decimals: " << std::fixed << std::setprecision(2) << val << "\n";
    std::cout << "Fixed 5 decimals: " << std::fixed << std::setprecision(5) << val << "\n";
    return 0;
}
