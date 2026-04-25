#pragma once
#include "Root.h"
#include "Branch.h"
#include <vector>
#include <string>


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
    Root root_;                    
    std::vector<Branch> branches_;
};
