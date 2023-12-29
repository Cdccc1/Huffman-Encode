#pragma once

#include <vector>

template <typename T>
class PriorityQueue {
public:
    PriorityQueue();

    // �����ȶ��������Ԫ��
    void push(T item);

    // �����ȶ������Ƴ����ȼ���ߵ�Ԫ��
    void pop();

    // ��ȡ���ȶ��������ȼ���ߵ�Ԫ��
    T top() const;

    // ������ȶ����Ƿ�Ϊ��
    bool isEmpty() const;

private:
    std::vector<T> heap;  // ���ڴ洢��Ԫ�ص�����

    // ������ά���ѵĸ�������
    void heapifyUp(int idx);      // ���ϵ�����
    void heapifyDown(int idx);    // ���µ�����
    int parent(int idx) const;    // ��ȡ���ڵ������
    int leftChild(int idx) const; // ��ȡ���ӽڵ������
    int rightChild(int idx) const;// ��ȡ���ӽڵ������
};
