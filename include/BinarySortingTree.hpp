#pragma once

#include "BinaryTreeNode.hpp"
#include <functional>
#include <memory>

namespace adsc {

template <typename T, typename Comparator = std::less<T>>
class BinarySortingTree {
public:

    explicit BinarySortingTree(Comparator comp = Comparator());

    virtual ~BinarySortingTree() = default;

    virtual void insert(T data) = 0;
    virtual void remove(const T& data) = 0;
    virtual T removeMin() = 0;
    virtual T removeMax() = 0;

    size_t nodesCount() const {return m_nodesCount;};
    size_t elementsCount() const {return m_elementsCount;};


    virtual bool search(const T& data) const {
        return searchRecursive(m_root, data);
    }

    bool empty() const;

    const std::unique_ptr<BinaryTreeNode<T>>& getRoot() const;

protected:
    bool searchRecursive(const std::unique_ptr<BinaryTreeNode<T>>& node, const T& data) const;

    std::unique_ptr<BinaryTreeNode<T>> m_root;
    Comparator m_comparator;

    size_t m_nodesCount{0};
    size_t m_elementsCount{0};
};

template <typename T, typename Comparator>
BinarySortingTree<T, Comparator>::BinarySortingTree(Comparator comp)
    : m_root(nullptr), m_comparator(std::move(comp)) {}


template <typename T, typename Comparator>
bool BinarySortingTree<T, Comparator>::empty() const {
    return m_root == nullptr;
}
    
template <typename T, typename Comparator>
const std::unique_ptr<BinaryTreeNode<T>>& BinarySortingTree<T, Comparator>::getRoot() const {
    return m_root;
}

template <typename T, typename Comparator>
bool BinarySortingTree<T, Comparator>::searchRecursive(const std::unique_ptr<BinaryTreeNode<T>>& node, const T& data) const {
    if (!node) return false;

    if (m_comparator(data, node->getData())) {
        return searchRecursive(node->getLeft(), data);
    } else if (m_comparator(node->getData(), data)) {
        return searchRecursive(node->getRight(), data);
    }
    return true; // Found the element
}

} // namespace adsc