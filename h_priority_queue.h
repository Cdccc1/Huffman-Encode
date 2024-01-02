#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class PriorityQueue {
public:
    PriorityQueue() {
        // 构造函数初始化为空的堆
    }

    void push(T item) {
        // 将新元素添加到堆的末尾
        heap.push_back(item);
        // 向上调整堆
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("尝试从空堆中pop");
        }
        // 将堆顶元素与最后一个元素交换
        std::swap(heap[0], heap.back());
        // 移除现在位于末尾的原堆顶元素
        heap.pop_back();
        // 向下调整堆
        heapifyDown(0);
    }

    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("尝试从空堆中获取top");
        }
        return heap.front();
    }

    bool isEmpty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

private:
    std::vector<T> heap;  // 用于存储堆元素的向量

    void heapifyUp(int idx) {
        while (idx > 0 && heap[parent(idx)] > heap[idx]) {
            std::swap(heap[parent(idx)], heap[idx]);
            idx = parent(idx);
        }
    }

    void heapifyDown(int idx) {
        int smallest = idx;
        int leftChildIdx = leftChild(idx);
        int rightChildIdx = rightChild(idx);

        if (leftChildIdx < heap.size() && heap[leftChildIdx] < heap[smallest]) {
            smallest = leftChildIdx;
        }

        if (rightChildIdx < heap.size() && heap[rightChildIdx] < heap[smallest]) {
            smallest = rightChildIdx;
        }

        if (smallest != idx) {
            std::swap(heap[idx], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int idx) const {
        return (idx - 1) / 2;
    }

    int leftChild(int idx) const {
        return 2 * idx + 1;
    }

    int rightChild(int idx) const {
        return 2 * idx + 2;
    }
};
