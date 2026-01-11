#include <gtest/gtest.h>
#include "BinaryTreeNode.hpp"

using adsc::BinaryTreeNode;

class BinaryTreeNodeTest : public ::testing::Test {};

TEST_F(BinaryTreeNodeTest, NodeInitialization) {
    BinaryTreeNode<int32_t> node(100);
    EXPECT_EQ(node.getData(), 100);
}

TEST_F(BinaryTreeNodeTest, InitialHeight) {
    auto node = std::make_unique<BinaryTreeNode<int>>(10);
    EXPECT_EQ(node->getHeight(), 1);
}

TEST_F(BinaryTreeNodeTest, UpdateHeightWithChildren) {
    auto root = std::make_unique<BinaryTreeNode<int>>(10);
    
    root->setLeft(std::make_unique<BinaryTreeNode<int>>(5));
    root->updateHeight();
    EXPECT_EQ(root->getHeight(), 2);

    root->setRight(std::make_unique<BinaryTreeNode<int>>(15));
    root->updateHeight();
    EXPECT_EQ(root->getHeight(), 2);

    root->getLeft()->setHeight(3); 
    root->updateHeight();
    EXPECT_EQ(root->getHeight(), 4);
}