#pragma once

#include "BinaryTree.hpp"

template <typename T, typename Comparator = std::less<T>>
class AVLTree : public BinaryTree<T, Comparator> {
public:
    AVLTree(Comparator comparator = Comparator());

    void insert(T data) override;
    // void remove(const T& data) override;

private:
    using TreeNodePtr = typename BinaryTree<T, Comparator>::TreeNodePtr;

    void recursive_insert_avl(TreeNodePtr& node, T data);
    // TreeNodePtr recursive_remove_avl(TreeNodePtr node, const T& data);

    void rebalance(TreeNodePtr& node);
    
    void rotateLeft(TreeNodePtr& node);
    void rotateRight(TreeNodePtr& node);

};

template <typename T, typename Comparator>
AVLTree<T, Comparator>::AVLTree(Comparator comparator)
: BinaryTree<T, Comparator>(comparator)
{}  

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::insert(T data) {
    this->m_elementsCount++;
    recursive_insert_avl(this->m_root, std::move(data));
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::recursive_insert_avl(TreeNodePtr& node, T data) {
    if (!node) {
        this->m_nodesCount++;
        node = std::make_unique<TreeNode<T>>(std::move(data));
        return;
    }

    if (data == node->getData()) {
        node->incrementCount();
    } else {
        if (this->m_comparator(data, node->getData())) {
            recursive_insert_avl(node->getLeft(), std::move(data));
        } else {
            recursive_insert_avl(node->getRight(), std::move(data));
        }
    }

    node->updateHeight();
    rebalance(node);
    return;
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::rebalance(TreeNodePtr& node) {
    if (!node) {
         return;
    }

    int32_t balance = node->getNodeBalance();

    // Left heavy
    if (balance > 1) {
        if (node->getLeft()->getNodeBalance() < 0) {
            // Left-Right case
            rotateLeft(node->getLeft());
        }
        rotateRight(node);
    }
    // Right heavy
    else if (balance < -1) {
        if (node->getRight()->getNodeBalance() > 0) {
            // Right-Left case
            rotateRight(node->getRight());
        }
        rotateLeft(node);
    }
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::rotateLeft(TreeNodePtr& node) {

    auto pivot = std::move(node->getRight());

    node->getRight() = std::move(pivot->getLeft());

    node->updateHeight();
    pivot->getLeft() = std::move(node);
    pivot->updateHeight();
    
    node = std::move(pivot);
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::rotateRight(TreeNodePtr& node) {

    auto pivot = std::move(node->getLeft());
    
    node->getLeft() = std::move(pivot->getRight());
    
    node->updateHeight();
    pivot->getRight() = std::move(node);
    pivot->updateHeight();
    
    node = std::move(pivot);
}