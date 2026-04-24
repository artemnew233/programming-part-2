#include <iostream>
#include <string>
#include <limits>

int main() {
    int i;
    double d;
    std::string word;
    std::string line;

    std::cout << "Enter an integer: ";
    std::cin >> i;

    std::cout << "Enter a float: ";
    std::cin >> d;

    std::cout << "Enter a word: ";
    std::cin >> word;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter a full line: ";
    std::getline(std::cin, line);

    std::cout << "\n--- You entered ---\n";
    std::cout << "Integer: " << i << "\n";
    std::cout << "Float:   " << d << "\n";
    std::cout << "Word:    " << word << "\n";
    std::cout << "Line:    " << line << "\n";
    return 0;
}
