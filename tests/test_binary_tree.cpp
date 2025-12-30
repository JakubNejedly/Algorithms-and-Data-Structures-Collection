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

TEST(BinaryTreeTest, DecrementCountTest) {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(50); 

    tree.remove(50); 
    ASSERT_NE(tree.getRoot(), nullptr);
    EXPECT_EQ(tree.getRoot()->getCount(), 1);

    tree.remove(50);
    EXPECT_EQ(tree.getRoot(), nullptr);
}

TEST(BinaryTreeTest, MetricsReflectReality) {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    EXPECT_EQ(tree.nodesCount(), 3);
    EXPECT_EQ(tree.elementsCount(), 4);

    tree.remove(50);
    EXPECT_EQ(tree.nodesCount(), 3);
    EXPECT_EQ(tree.elementsCount(), 3);

    tree.remove(50);
    EXPECT_EQ(tree.nodesCount(), 2);
    EXPECT_EQ(tree.elementsCount(), 2);
}

TEST(BinaryTreeTest, RemoveMinWithMultipleCounts) {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(10);
    tree.insert(20);

    EXPECT_EQ(tree.removeMin(), 10);
    ASSERT_NE(tree.getRoot(), nullptr);
    EXPECT_EQ(tree.getRoot()->getCount(), 1);


    EXPECT_EQ(tree.removeMin(), 10);
    EXPECT_EQ(tree.getRoot()->getData(), 20);
    EXPECT_EQ(tree.getRoot()->getLeft(), nullptr);
    EXPECT_EQ(tree.getRoot()->getRight(), nullptr);
}


