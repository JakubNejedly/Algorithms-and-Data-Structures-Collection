#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>

template <typename T>
class TreeNode {
public:
    TreeNode(T data);
 
    const T& getData() const { return m_data; };

    void setLeft(std::unique_ptr<TreeNode<T>> left) { m_left = std::move(left); };
    std::unique_ptr<TreeNode<T>>& getLeft() {return m_left; };

    void setRight(std::unique_ptr<TreeNode<T>> right) { m_right = std::move(right); };
    std::unique_ptr<TreeNode<T>>& getRight() {return m_right; };

    void incrementCount() { m_count++; }    
    bool decrementCount();
    uint32_t getCount() const { return m_count; }   
    void setCount(uint32_t count) { m_count = count; }

    uint32_t calculateDepth() const;
    int32_t calculateBalance() const;

protected:
    const T m_data;

    uint32_t m_count;

    std::unique_ptr<TreeNode<T>> m_left;
    std::unique_ptr<TreeNode<T>> m_right;
};

template <typename T>
TreeNode<T>::TreeNode(T data)
: m_data(std::move(data))
, m_count(1)
, m_left(nullptr)
, m_right(nullptr)
{}


template <typename T>
bool TreeNode<T>::decrementCount() {
    if (m_count > 0) {
        m_count--;
    }
    return m_count > 0;
}

template <typename T>
uint32_t TreeNode<T>::calculateDepth() const {
    uint32_t leftDepth = (m_left) ? m_left->calculateDepth() : 0;
    uint32_t rightDepth = (m_right) ? m_right->calculateDepth() : 0;
    return 1 + std::max(leftDepth, rightDepth);
}

template <typename T>
int32_t TreeNode<T>::calculateBalance() const {
    uint32_t leftDepth = (m_left) ? m_left->calculateDepth() : 0;
    uint32_t rightDepth = (m_right) ? m_right->calculateDepth() : 0;
    return static_cast<int32_t>(leftDepth) - rightDepth;
}