#include "h_priority_queue.h"
#include <stdexcept>

template <typename T>
PriorityQueue<T>::PriorityQueue() {
    // 构造函数初始化为空的堆
}

template <typename T>
void PriorityQueue<T>::push(T item) {
    // 将新元素添加到堆的末尾
    heap.push_back(item);
    // 向上调整堆
    heapifyUp(heap.size() - 1);
}

template <typename T>
void PriorityQueue<T>::pop() {
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

template <typename T>
T PriorityQueue<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("尝试从空堆中获取top");
    }
    return heap.front();
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return heap.empty();
}

template <typename T>
size_t PriorityQueue<T>::size() const{
    return heap.size();
}

template <typename T>
void PriorityQueue<T>::heapifyUp(int idx) {
    while (idx > 0 && heap[parent(idx)] > heap[idx]) {
        std::swap(heap[parent(idx)], heap[idx]);
        idx = parent(idx);
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int idx) {
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

template <typename T>
int PriorityQueue<T>::parent(int idx) const {
    return (idx - 1) / 2;
}

template <typename T>
int PriorityQueue<T>::leftChild(int idx) const {
    return 2 * idx + 1;
}

template <typename T>
int PriorityQueue<T>::rightChild(int idx) const {
    return 2 * idx + 2;
}

// 显式模板实例化
template class PriorityQueue<int>;
