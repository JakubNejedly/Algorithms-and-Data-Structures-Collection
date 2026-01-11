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

    uint32_t getHeight() const { return m_height; }
    void setHeight(uint32_t height) { m_height = height; }

    void updateHeight();
    int32_t getNodeBalance() const;

protected:
    const T m_data;

    uint32_t m_count;

    uint32_t m_height;

    std::unique_ptr<TreeNode<T>> m_left;
    std::unique_ptr<TreeNode<T>> m_right;
};

template <typename T>
TreeNode<T>::TreeNode(T data)
: m_data(std::move(data))
, m_count(1)
, m_height(1)
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
void TreeNode<T>::updateHeight() {
    uint32_t leftHeight = m_left ? m_left->getHeight() : 0;
    uint32_t rightHeight = m_right ? m_right->getHeight() : 0;
    m_height = 1 + std::max(leftHeight, rightHeight);
}

template <typename T>
int32_t TreeNode<T>::getNodeBalance() const {
    int32_t leftH = m_left ? m_left->getHeight() : 0;
    int32_t rightH = m_right ? m_right->getHeight() : 0;
    return leftH - rightH;
}