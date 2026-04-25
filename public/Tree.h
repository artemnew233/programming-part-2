#pragma once
#include "Root.h"
#include "Branch.h"
#include <vector>
#include <string>

// Tree is the composite whole. Root and Branch (which contain Leaf and Fruit)
// are integral composition parts — they cannot exist without the Tree context.
class Tree {
public:
    Tree(std::string species, double heightM, Root root);
    void addBranch(Branch branch);
    const std::string& getSpecies() const;
    double getHeight() const;
    const Root& getRoot() const;
    const std::vector<Branch>& getBranches() const;
    int totalLeaves() const;
    int totalFruits() const;
    double totalFruitWeight() const;
    std::string describe() const;
private:
    std::string species_;
    double heightM_;
    Root root_;                    // composition: one root, lifetime bound to Tree
    std::vector<Branch> branches_; // composition: branches are integral parts
};
