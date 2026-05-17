#pragma once
#include "Leaf.h"
#include "Fruit.h"
#include <vector>
#include <string>

class Branch {
public:
    explicit Branch(double lengthCm, int order = 1);
    void addLeaf(Leaf leaf);
    void addFruit(Fruit fruit);
    double getLength() const;
    int getOrder() const;
    int leafCount() const;
    int fruitCount() const;
    double totalFruitWeight() const;
    std::string describe() const;
private:
    double lengthCm_;
    int order_;
    std::vector<Leaf> leaves_;
    std::vector<Fruit> fruits_;
};
