#include "Tree.h"
#include <iostream>

int main() {    // Tree owns Root and Branches -->  Branches own Leaves and Fruits.
    Root root(120.0, "taproot");
    Tree apple("Malus domestica", 4.5, std::move(root));

    // First branch
    Branch b1(80.0, 1);
    b1.addLeaf(Leaf(7.5, "green"));
    b1.addLeaf(Leaf(6.0, "green"));
    b1.addLeaf(Leaf(5.5, "yellow"));
    b1.addFruit(Fruit("apple", 180.0));
    b1.addFruit(Fruit("apple", 210.0));
    apple.addBranch(std::move(b1));

    // Second branch
    Branch b2(65.0, 1);
    b2.addLeaf(Leaf(8.0, "green"));
    b2.addLeaf(Leaf(7.0, "green"));
    b2.addFruit(Fruit("apple", 195.0));
    apple.addBranch(std::move(b2));

    // Third branch
    Branch b3(30.0, 2);
    b3.addLeaf(Leaf(4.5, "green"));
    b3.addLeaf(Leaf(5.0, "green"));
    apple.addBranch(std::move(b3));

    std::cout << apple.describe() << "\n\n";
    std::cout << "Total leaves : " << apple.totalLeaves() << "\n";
    std::cout << "Total fruits : " << apple.totalFruits() << "\n";
    std::cout << "Fruit weight : " << apple.totalFruitWeight() << " g\n";

    return 0;
}
