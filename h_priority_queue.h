#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class PriorityQueue {
public:
    PriorityQueue() {
        // ���캯����ʼ��Ϊ�յĶ�
    }

    void push(T item) {
        // ����Ԫ����ӵ��ѵ�ĩβ
        heap.push_back(item);
        // ���ϵ�����
        heapifyUp(heap.size() - 1);
    }

    void pop() {
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

    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("���Դӿն��л�ȡtop");
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
    std::vector<T> heap;  // ���ڴ洢��Ԫ�ص�����

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
