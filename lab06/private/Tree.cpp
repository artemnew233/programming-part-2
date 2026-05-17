#include "Tree.h"
#include <sstream>

Tree::Tree(std::string species, double heightM, Root root)
    : species_(std::move(species)), heightM_(heightM), root_(std::move(root)) {}

void Tree::addBranch(Branch branch) { branches_.push_back(std::move(branch)); }
const std::string& Tree::getSpecies() const { return species_; }
double Tree::getHeight() const { return heightM_; }
const Root& Tree::getRoot() const { return root_; }
const std::vector<Branch>& Tree::getBranches() const { return branches_; }

int Tree::totalLeaves() const {
    int count = 0;
    for (const auto& b : branches_) count += b.leafCount();
    return count;
}

int Tree::totalFruits() const {
    int count = 0;
    for (const auto& b : branches_) count += b.fruitCount();
    return count;
}

double Tree::totalFruitWeight() const {
    double total = 0.0;
    for (const auto& b : branches_) total += b.totalFruitWeight();
    return total;
}

std::string Tree::describe() const {
    std::ostringstream oss;
    oss << "Tree[" << species_ << ", height=" << heightM_ << "m, "
        << branches_.size() << " branches, "
        << totalLeaves() << " leaves, "
        << totalFruits() << " fruits ("
        << totalFruitWeight() << "g total)]\n"
        << "  " << root_.describe();
    for (const auto& b : branches_) {
        oss << "\n  " << b.describe();
    }
    return oss.str();
}
