#pragma once

#include <vector>

template <typename T>
class PriorityQueue {
public:
    PriorityQueue();

    // 向优先队列中添加元素
    void push(T item);

    // 从优先队列中移除优先级最高的元素
    void pop();

    // 获取优先队列中优先级最高的元素
    T top() const;

    // 检查优先队列是否为空
    bool isEmpty() const;

private:
    std::vector<T> heap;  // 用于存储堆元素的向量

    // 以下是维护堆的辅助函数
    void heapifyUp(int idx);      // 向上调整堆
    void heapifyDown(int idx);    // 向下调整堆
    int parent(int idx) const;    // 获取父节点的索引
    int leftChild(int idx) const; // 获取左子节点的索引
    int rightChild(int idx) const;// 获取右子节点的索引
};
