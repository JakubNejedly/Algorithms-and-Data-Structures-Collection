#pragma once

#include "SortingTree.hpp"

template <typename T, typename Comparator = std::less<T>>
class BinaryTree : public SortingTree<T, Comparator> {
public:
    BinaryTree(Comparator comparator = Comparator());

    virtual void insert(T data) override;
    virtual void remove(const T& data) override;
    T removeMin() override;
    T removeMax() override;

protected:
    using SortingTree<T, Comparator>::m_root;
    using SortingTree<T, Comparator>::m_comparator;

    using TreeNodePtr = std::unique_ptr<TreeNode<T>>;

    // Helper for insert
    void recursive_insert(TreeNodePtr& node, T data);
    
    // Helpers for remove
    TreeNodePtr recursive_remove(TreeNodePtr node, const T& data);
    TreeNodePtr extractMin(TreeNodePtr& node);
    
    // Helper for removeMin
    TreeNodePtr recursive_remove_min(TreeNodePtr node, T& outData);

    // Helper for removeMax
    TreeNodePtr recursive_remove_max(TreeNodePtr node, T& outData);
};

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree(Comparator comparator)
: SortingTree<T, Comparator>(comparator)
{}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::insert(T data) {
    this->m_elementsCount++;
    recursive_insert(m_root, std::move(data));
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::recursive_insert(TreeNodePtr& node, T data) {
    if (!node) {
        this->m_nodesCount++;
        node = std::make_unique<TreeNode<T>>(std::move(data));
        return;
    }

    if (data == node->getData()) {
        node->incrementCount();
    }else {
        if (m_comparator(data, node->getData())) {
            recursive_insert(node->getLeft(), std::move(data));
        } else {
            recursive_insert(node->getRight(), std::move(data));
        }
    }

    node->updateHeight();
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::remove(const T& data) {
    m_root = recursive_remove(std::move(m_root), data);
}

template <typename T, typename Comparator>
typename BinaryTree<T, Comparator>::TreeNodePtr
BinaryTree<T, Comparator>::recursive_remove(TreeNodePtr node, const T& data) {
    if (!node){
        // Node with data not found
        return nullptr;
    }

    if (m_comparator(data, node->getData())) {
        node->getLeft() = recursive_remove(std::move(node->getLeft()), data);
    } else if (m_comparator(node->getData(), data)) {
        node->getRight() = recursive_remove(std::move(node->getRight()), data);
    } else {
        // Data found
        bool anyLeft = node->decrementCount();
        this->m_elementsCount--;
        if (anyLeft) {
            return node;
        }

        // Remmove node with only no or one child
        this->m_nodesCount--;  
        if (!node->getLeft()) return std::move(node->getRight());
        if (!node->getRight()) return std::move(node->getLeft());

        // Node with two children
        TreeNodePtr successor = extractMin(node->getRight());
        successor->setLeft(std::move(node->getLeft()));
        successor->setRight(std::move(node->getRight()));
        node = std::move(successor);
    }

    node->updateHeight();
    return node;
}

template <typename T, typename Comparator>
typename BinaryTree<T, Comparator>::TreeNodePtr
BinaryTree<T, Comparator>::extractMin(TreeNodePtr& node) {
    if (node->getLeft()) {
        TreeNodePtr minNode = extractMin(node->getLeft());
        node->updateHeight();
        return minNode; 
    }

    auto minNode = std::move(node);
    node = std::move(minNode->getRight()); 
    return minNode;
}

template <typename T, typename Comparator>
T BinaryTree<T, Comparator>::removeMin() {
    if (this->empty()) {
        throw std::runtime_error("Tree is empty");
    }

    this->m_elementsCount--;
    T result_data; 
    m_root = recursive_remove_min(std::move(m_root), result_data);
    return result_data;
}

template <typename T, typename Comparator>
typename BinaryTree<T, Comparator>::TreeNodePtr
BinaryTree<T, Comparator>::recursive_remove_min(TreeNodePtr node, T& outData) {
    // Iterate to find min value
    if (node->getLeft()) {
        node->getLeft() = recursive_remove_min(std::move(node->getLeft()), outData);
        node->updateHeight();
        return node;
    }

    outData = node->getData();
    // Decrement count
    bool anyLeft = node->decrementCount();
    if (anyLeft) {
        return node;
    }
    // Replace node with its right child
    this->m_nodesCount--;
    return std::move(node->getRight());
}

template <typename T, typename Comparator>
T BinaryTree<T, Comparator>::removeMax() {
    if (this->empty()) {
        throw std::runtime_error("Tree is empty");
    }

    this->m_elementsCount--;
    T result_data; 
    m_root = recursive_remove_max(std::move(m_root), result_data);
    return result_data;
}

template <typename T, typename Comparator>
typename BinaryTree<T, Comparator>::TreeNodePtr
BinaryTree<T, Comparator>::recursive_remove_max(TreeNodePtr node, T& outData) {
    // Iterate to find max value
    if (node->getRight()) {
        node->getRight() = recursive_remove_max(std::move(node->getRight()), outData);
        return node;
    }

    outData = node->getData();
    // Decrement count
    bool anyLeft = node->decrementCount();
    if (anyLeft) {
        return node;
    }

    // Replace node with its left child
    this->m_nodesCount--;
    return std::move(node->getLeft());
}