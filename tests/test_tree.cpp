#include <gtest/gtest.h>
#include "Tree.h"

TEST(FruitTest, BasicAttributes) {
    Fruit f("apple", 150.0);
    EXPECT_EQ(f.getType(), "apple");
    EXPECT_DOUBLE_EQ(f.getWeight(), 150.0);
}

TEST(LeafTest, HealthyLeaf) {
    Leaf green(5.0, "green");
    EXPECT_TRUE(green.isHealthy());
    Leaf yellow(5.0, "yellow");
    EXPECT_FALSE(yellow.isHealthy());
    Leaf tiny(0.3, "green");
    EXPECT_FALSE(tiny.isHealthy());
}

TEST(BranchTest, AddLeavesAndFruits) {
    Branch b(60.0, 1);
    b.addLeaf(Leaf(5.0));
    b.addLeaf(Leaf(6.0));
    b.addFruit(Fruit("apple", 200.0));
    EXPECT_EQ(b.leafCount(), 2);
    EXPECT_EQ(b.fruitCount(), 1);
    EXPECT_DOUBLE_EQ(b.totalFruitWeight(), 200.0);
}

TEST(RootTest, WaterAbsorption) {
    Root r(100.0, "taproot");
    EXPECT_DOUBLE_EQ(r.waterAbsorptionRate(), 5.0);
}

TEST(TreeTest, TotalsAreCorrect) {
    Root root(80.0);
    Tree t("Oak", 10.0, std::move(root));

    Branch b1(50.0);
    b1.addLeaf(Leaf(4.0));
    b1.addLeaf(Leaf(5.0));
    b1.addFruit(Fruit("acorn", 3.0));
    t.addBranch(std::move(b1));

    Branch b2(40.0);
    b2.addLeaf(Leaf(6.0));
    b2.addFruit(Fruit("acorn", 4.0));
    b2.addFruit(Fruit("acorn", 5.0));
    t.addBranch(std::move(b2));

    EXPECT_EQ(t.totalLeaves(), 3);
    EXPECT_EQ(t.totalFruits(), 3);
    EXPECT_DOUBLE_EQ(t.totalFruitWeight(), 12.0);
}

TEST(TreeTest, DescribeContainsSpecies) {
    Root root(50.0);
    Tree t("Birch", 6.0, std::move(root));
    EXPECT_NE(t.describe().find("Birch"), std::string::npos);
}
