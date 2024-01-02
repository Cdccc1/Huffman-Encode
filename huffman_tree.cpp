#include "huffman_tree.h"

// ��ʽʵ����
template class PriorityQueue<HuffmanTree::Node*>;




// ���캯��
HuffmanTree::HuffmanTree() : root(nullptr) {}

// ��������
HuffmanTree::~HuffmanTree() {
    freeTree(root);
}

// �ݹ��ͷ����ڴ�
void HuffmanTree::freeTree(Node* node) {
    if (node != nullptr) {
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
}

// ����ͳ�Ƶ��ַ�Ƶ�ʱ�������������ʵ�ֵ�С�����Ż�
void HuffmanTree::buildTree(const std::map<std::wstring, int>& frequencies) {
    PriorityQueue<Node*> pq;
    for (auto& pair : frequencies) {
        pq.push(new Node(pair.first[0], pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node(L'\0', left->frequency + right->frequency, left, right);
        pq.push(parent);
    }

    root = pq.top();
}

// ������������
std::map<wchar_t, std::wstring> HuffmanTree::encode() {
    std::map<wchar_t, std::wstring> codeMap;
    encodeHelper(root, L"", codeMap);
    return codeMap;
}

// �ݹ����Helper
void HuffmanTree::encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap) {
    if (!node) return;
    if (!node->left && !node->right) {
        codeMap[node->character] = code;
    }
    encodeHelper(node->left, code + L"0", codeMap);
    encodeHelper(node->right, code + L"1", codeMap);
}

// ���ڽ���ĺ���
std::wstring HuffmanTree::decode(const std::wstring& encodedStr) {
    std::wstring decoded;
    Node* current = root;
    for (wchar_t bit : encodedStr) {
        if (bit == L'0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        // ����Ҷ�ӽڵ�
        if (!current->left && !current->right) {
            decoded += current->character;
            current = root; // ����Ϊ���ڵ㿪ʼ��һ���ַ��Ľ���
        }
    }
    return decoded;
}
