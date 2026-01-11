#include <gtest/gtest.h>
#include "AVLTree.hpp"

class AVLTreeTest : public ::testing::Test {
protected:
    AVLTree<int> avl;
};


TEST_F(AVLTreeTest, RightRotationLL) {
    avl.insert(30);
    avl.insert(20);
    avl.insert(10);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
    EXPECT_EQ(avl.getRoot()->getHeight(), 2);
}


TEST_F(AVLTreeTest, LeftRotationRR) {
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
    EXPECT_EQ(avl.getRoot()->getHeight(), 2);
}

TEST_F(AVLTreeTest, DoubleRotationLR) {
    avl.insert(30);
    avl.insert(10);
    avl.insert(20);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
}

TEST_F(AVLTreeTest, DoubleRotationRL) {
    avl.insert(10);
    avl.insert(30);
    avl.insert(20);

    ASSERT_NE(avl.getRoot(), nullptr);
    EXPECT_EQ(avl.getRoot()->getData(), 20);
    EXPECT_EQ(avl.getRoot()->getLeft()->getData(), 10);
    EXPECT_EQ(avl.getRoot()->getRight()->getData(), 30);
}

TEST_F(AVLTreeTest, BalancedHeightLargeScale) {
    for (int i = 1; i <= 100; ++i) {
        avl.insert(i);
    }

    EXPECT_LE(avl.getRoot()->getHeight(), 8);
    EXPECT_EQ(avl.elementsCount(), 100);
}