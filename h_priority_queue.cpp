#include "h_priority_queue.h"
#include <stdexcept>

template <typename T>
PriorityQueue<T>::PriorityQueue() {
    // ���캯����ʼ��Ϊ�յĶ�
}

template <typename T>
void PriorityQueue<T>::push(T item) {
    // ����Ԫ����ӵ��ѵ�ĩβ
    heap.push_back(item);
    // ���ϵ�����
    heapifyUp(heap.size() - 1);
}

template <typename T>
void PriorityQueue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("���Դӿն���pop");
    }
    // ���Ѷ�Ԫ�������һ��Ԫ�ؽ���
    std::swap(heap[0], heap.back());
    // �Ƴ�����λ��ĩβ��ԭ�Ѷ�Ԫ��
    heap.pop_back();
    // ���µ�����
    heapifyDown(0);
}

template <typename T>
T PriorityQueue<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("���Դӿն��л�ȡtop");
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

// ��ʽģ��ʵ����
template class PriorityQueue<int>;
