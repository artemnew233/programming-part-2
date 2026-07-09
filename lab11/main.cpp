#include "RouteTable.h"
#include "RouteRecord.h"
#include "DistancePolicy.h"
#include <iostream>
#include <string>

int main() {
    // --- Part 1: RouteTable<T, N> ---
    std::cout << "=== RouteTable<int, 5> ===\n";
    RouteTable<int, 5> tableInt;
    tableInt.set(0, 120);
    tableInt.set(1, 350);
    tableInt.set(2, 85);
    tableInt.set(3, 410);
    tableInt.set(4, 200);

    std::cout << "Count    : " << tableInt.count() << "\n";
    std::cout << "Longest  : " << tableInt.longest() << " km\n";
    std::cout << "Shortest : " << tableInt.shortest() << " km\n";
    std::cout << "Average  : " << tableInt.average() << " km\n";

    std::cout << "\n=== RouteTable<double, 4> ===\n";
    RouteTable<double, 4> tableDouble;
    tableDouble.set(0, 1.5);
    tableDouble.set(1, 3.2);
    tableDouble.set(2, 0.8);
    tableDouble.set(3, 2.7);

    std::cout << "Longest  : " << tableDouble.longest() << " h\n";
    std::cout << "Shortest : " << tableDouble.shortest() << " h\n";
    std::cout << "Average  : " << tableDouble.average() << " h\n";

    // Out-of-range protection
    try { tableInt.get(10); }
    catch (const std::out_of_range& e) {
        std::cout << "\nExpected exception: " << e.what() << "\n";
    }

    // --- Part 2a: RouteRecord ---
    std::cout << "\n=== RouteRecord ===\n";
    RouteRecord<std::string, int> r1("A->B", 250);
    RouteRecord<int, double>      r2(42, 3.14);
    std::cout << r1.toString() << "\n";
    std::cout << r2.toString() << "\n";

    // --- Part 2b: DistancePolicy specializations ---
    std::cout << "\n=== DistancePolicy ===\n";
    // Integer: exact
    std::cout << "int   equal(5, 5)              : "
              << std::boolalpha << DistancePolicy<int>::equal(5, 5) << "\n";
    std::cout << "int   equal(5, 6)              : "
              << DistancePolicy<int>::equal(5, 6) << "\n";

    // Double: approximate (epsilon = 1e-9)
    std::cout << "double equal(1.0, 1.0+1e-10)   : "
              << DistancePolicy<double>::equal(1.0, 1.0 + 1e-10) << "\n"; // true
    std::cout << "double equal(1.0, 1.0+1e-8)    : "
              << DistancePolicy<double>::equal(1.0, 1.0 + 1e-8) << "\n";  // false

    // --- Compiler-oriented investigation ---
    std::cout << "\n=== sizeof (compiler instantiation) ===\n";
    std::cout << "sizeof(RouteTable<int,5>)              = " << sizeof(RouteTable<int,5>) << "\n";
    std::cout << "sizeof(RouteTable<double,5>)           = " << sizeof(RouteTable<double,5>) << "\n";
    std::cout << "sizeof(RouteTable<int,10>)             = " << sizeof(RouteTable<int,10>) << "\n";
    std::cout << "sizeof(RouteRecord<string,int>)        = " << sizeof(RouteRecord<std::string,int>) << "\n";
    std::cout << "sizeof(RouteRecord<int,double>)        = " << sizeof(RouteRecord<int,double>) << "\n";
    // Each instantiation is a separate, independently compiled type.

    return 0;
}
