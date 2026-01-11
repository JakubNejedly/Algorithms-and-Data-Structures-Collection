#pragma once

#include "BinaryTree.hpp"

namespace adsc {

template <typename T, typename Comparator = std::less<T>>
class AVLTree : public BinaryTree<T, Comparator> {
public:
    AVLTree(Comparator comparator = Comparator());
    ~AVLTree() = default;

    void insert(T data) override;
    void remove(const T& data) override;
    T removeMin() override;
    T removeMax() override;

private:
    using SortingTree<T, Comparator>::m_root;
    
    using TreeNodePtr = typename BinaryTree<T, Comparator>::TreeNodePtr;

    // Helper for insert
    void recursive_insert(TreeNodePtr& node, T data);

    // Helpers for remove
    void recursive_remove(TreeNodePtr& node, const T& data);
    TreeNodePtr extractMin(TreeNodePtr& node); 

    // Helper for removeMin
    T recursive_remove_min(TreeNodePtr& node);

    // Helper for removeMax
    T recursive_remove_max(TreeNodePtr& node);

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
    recursive_insert(m_root, std::move(data));
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::recursive_insert(TreeNodePtr& node, T data) {
    if (!node) {
        this->m_nodesCount++;
        node = std::make_unique<TreeNode<T>>(std::move(data));
        return;
    }

    if (data == node->getData()) {
        node->incrementCount();
    } else {
        if (this->m_comparator(data, node->getData())) {
            recursive_insert(node->getLeft(), std::move(data));
        } else {
            recursive_insert(node->getRight(), std::move(data));
        }
    }

    node->updateHeight();
    rebalance(node);
    return;
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::remove(const T& data) {
    recursive_remove(m_root, data);
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::recursive_remove(TreeNodePtr& node, const T& data) {
    if (!node){
        // Record not found
        return;
    }

    if (this->m_comparator(data, node->getData())) {
        recursive_remove(node->getLeft(), data);
    } else if (this->m_comparator(node->getData(), data)) {
        recursive_remove(node->getRight(), data);
    } else {
        // Data found
        if (node->decrementCount()) {
            this->m_elementsCount--;
            return;
        }

        this->m_elementsCount--;
        this->m_nodesCount--;

        if (!node->getLeft()) {
            // Only right child case
            node = std::move(node->getRight());
            return;
        } 
        else if (!node->getRight()) {
            // Only left child case
            node = std::move(node->getLeft());
            return;
        } 
        else {
            // Two children case
            TreeNodePtr successor = extractMin(node->getRight());
            successor->getLeft() = std::move(node->getLeft());
            successor->getRight() = std::move(node->getRight());
            node = std::move(successor);
        }
    }

    if (node) {
        node->updateHeight();
        rebalance(node);
    }
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::TreeNodePtr 
AVLTree<T, Comparator>::extractMin(TreeNodePtr& node) {
    if (node->getLeft()) {
        TreeNodePtr minNode = extractMin(node->getLeft());
        node->updateHeight();
        rebalance(node);
        return minNode;
    }

    TreeNodePtr minNode = std::move(node);
    node = std::move(minNode->getRight());
    return minNode;
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::removeMin() {
    if (this->empty()) {
        throw std::runtime_error("Tree is empty");
    }
    this->m_elementsCount--;
    return std::move(recursive_remove_min(m_root));
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::recursive_remove_min(TreeNodePtr& node) {
    // Iterate to find min value
    if (node->getLeft()) {
        T outData = std::move(recursive_remove_min(node->getLeft()));
        node->updateHeight();
        rebalance(node);
        return std::move(outData);
    }

    T outData = std::move(node->getData());
    if (node->decrementCount()) {
        // Only decrement count
        return std::move(outData);
    }
    // Replace node with its right child
    this->m_nodesCount--;
    node = std::move(node->getRight());
    return std::move(outData);
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::removeMax() {
    if (this->empty()) {
        throw std::runtime_error("Tree is empty");
    }
    this->m_elementsCount--;
    return std::move(recursive_remove_max(m_root));
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::recursive_remove_max(TreeNodePtr& node) {
    // Iterate to find max value
    if (node->getRight()) {
        T outData = std::move(recursive_remove_max(node->getRight()));
        node->updateHeight();
        rebalance(node);
        return std::move(outData);
    }

    T outData = std::move(node->getData());
    if (node->decrementCount()) {
        // Only decrement count
        return std::move(outData);
    }
    // Replace node with its left child
    this->m_nodesCount--;
    node = std::move(node->getLeft());  
    return std::move(outData);
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

} // namespace adsc