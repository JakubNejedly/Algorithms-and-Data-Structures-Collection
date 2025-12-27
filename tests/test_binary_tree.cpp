#include <gtest/gtest.h>
#include "BinaryTree.hpp"

TEST(BinaryTreeTest, IsEmpty) {
    BinaryTree<uint32_t> tree;
    EXPECT_TRUE(tree.empty());
    tree.insert(10);
    EXPECT_FALSE(tree.empty());
}

TEST(BinaryTreeTest, BasicInsertion) {
    BinaryTree<int32_t> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    EXPECT_EQ(tree.getRoot()->getData(), 10);
    EXPECT_EQ(tree.getRoot()->getLeft()->getData(), 5);
    EXPECT_EQ(tree.getRoot()->getRight()->getData(), 15);
    EXPECT_EQ(tree.getRoot()->getLeft()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getLeft()->getRight(), nullptr);
    EXPECT_EQ(tree.getRoot()->getRight()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getRight()->getRight(), nullptr);
}


