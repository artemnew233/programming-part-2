#include "Branch.h"
#include <sstream>
#include <numeric>

Branch::Branch(double lengthCm, int order)
    : lengthCm_(lengthCm), order_(order) {}

void Branch::addLeaf(Leaf leaf) { leaves_.push_back(std::move(leaf)); }
void Branch::addFruit(Fruit fruit) { fruits_.push_back(std::move(fruit)); }
double Branch::getLength() const { return lengthCm_; }
int Branch::getOrder() const { return order_; }
int Branch::leafCount() const { return static_cast<int>(leaves_.size()); }
int Branch::fruitCount() const { return static_cast<int>(fruits_.size()); }

double Branch::totalFruitWeight() const {
    double total = 0.0;
    for (const auto& f : fruits_) total += f.getWeight();
    return total;
}

std::string Branch::describe() const {
    std::ostringstream oss;
    oss << "Branch[order=" << order_ << ", len=" << lengthCm_ << "cm, "
        << leaves_.size() << " leaves, " << fruits_.size() << " fruits]";
    return oss.str();
}
