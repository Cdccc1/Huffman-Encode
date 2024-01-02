#include "huffman_tree.h"

// 显式实例化
template class PriorityQueue<HuffmanTree::Node*>;




// 构造函数
HuffmanTree::HuffmanTree() : root(nullptr) {}

// 析构函数
HuffmanTree::~HuffmanTree() {
    freeTree(root);
}

// 递归释放树内存
void HuffmanTree::freeTree(Node* node) {
    if (node != nullptr) {
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
}

// 利用统计的字符频率表建树，利用自行实现的小根堆优化
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

// 哈夫曼树编码
std::map<wchar_t, std::wstring> HuffmanTree::encode() {
    std::map<wchar_t, std::wstring> codeMap;
    encodeHelper(root, L"", codeMap);
    return codeMap;
}

// 递归编码Helper
void HuffmanTree::encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap) {
    if (!node) return;
    if (!node->left && !node->right) {
        codeMap[node->character] = code;
    }
    encodeHelper(node->left, code + L"0", codeMap);
    encodeHelper(node->right, code + L"1", codeMap);
}

// 用于解码的函数
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

        // 到达叶子节点
        if (!current->left && !current->right) {
            decoded += current->character;
            current = root; // 重置为根节点开始下一个字符的解码
        }
    }
    return decoded;
}
