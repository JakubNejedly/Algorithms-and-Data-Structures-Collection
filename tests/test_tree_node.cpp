#include <gtest/gtest.h>
#include "TreeNode.hpp"

using adsc::TreeNode;

class TreeNodeTest : public ::testing::Test {};

TEST_F(TreeNodeTest, NodeInitialization) {
    TreeNode<int32_t> node(100);
    EXPECT_EQ(node.getData(), 100);
}

TEST_F(TreeNodeTest, InitialHeight) {
    auto node = std::make_unique<TreeNode<int>>(10);
    EXPECT_EQ(node->getHeight(), 1);
}

TEST_F(TreeNodeTest, UpdateHeightWithChildren) {
    auto root = std::make_unique<TreeNode<int>>(10);
    
    root->setLeft(std::make_unique<TreeNode<int>>(5));
    root->updateHeight();
    EXPECT_EQ(root->getHeight(), 2);

    root->setRight(std::make_unique<TreeNode<int>>(15));
    root->updateHeight();
    EXPECT_EQ(root->getHeight(), 2);

    root->getLeft()->setHeight(3); 
    root->updateHeight();
    EXPECT_EQ(root->getHeight(), 4);
}