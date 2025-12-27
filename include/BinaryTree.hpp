#pragma once

#include "SortingTree.hpp"

template <typename T, typename Comparator = std::less<T>>
class BinaryTree : public SortingTree<T, Comparator> {
public:
    BinaryTree(Comparator comparator = Comparator());

    void insert(T data) override;
    void remove(const T& data) override {} // Removal not implemented;

private:
    using SortingTree<T, Comparator>::m_root;
    using SortingTree<T, Comparator>::m_comparator;

    void recursive_insert(std::unique_ptr<TreeNode<T>>& node, T data);

};

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree(Comparator comparator)
: SortingTree<T, Comparator>(comparator)
{}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::insert(T data) {
    recursive_insert(m_root, std::move(data));
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::recursive_insert(std::unique_ptr<TreeNode<T>>& node, T data) {
    if (!node) {
        node = std::make_unique<TreeNode<T>>(std::move(data));
        return;
    }

    if (m_comparator(data, node->getData())) {
        recursive_insert(node->getLeft(), std::move(data));
    } else {
        recursive_insert(node->getRight(), std::move(data));
    }
}
