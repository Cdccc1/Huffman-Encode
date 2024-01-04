#include "huffman_tree.h"

// ��ʽʵ����
template class PriorityQueue<HuffmanTree::Node*, HuffmanTree::Cmp>;


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
void HuffmanTree::buildTree(const std::map<std::string, int>& frequencies) {
    PriorityQueue<Node*, HuffmanTree::Cmp> pq;
    for (auto& pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node("", left->frequency + right->frequency, left, right);
        pq.push(parent);
    }

    root = pq.top();
    
}

// ���ظ��ڵ�ָ��
HuffmanTree::Node* HuffmanTree::getRoot() const {
    return root; 
}

// ������������
std::map<std::string, std::vector<bool>> HuffmanTree::encode() {
    std::map<std::string, std::vector<bool>> codeMap;
    encodeHelper(root, std::vector<bool>(), codeMap);

    // ����codeMap����ӡ�ַ������Ӧ�ı���
    /*
    for (const auto& pair : codeMap) {
        std::cout << "Character: " << pair.first << " | Code: ";
        for (bool bit : pair.second) {
            std::cout << bit;
        }
        std::cout << std::endl;
    }
    */

    return codeMap;
}


// �ݹ����Helper
// �޸Ĳ�������Ϊ std::vector<bool>������Ӧ��̬���ȵı���
void HuffmanTree::encodeHelper(Node* node, std::vector<bool> code, std::map<std::string, std::vector<bool>>& codeMap) {
    if (!node) return;
    if (!node->left && !node->right) {
        // ������Ҷ�ӽڵ�ʱ����������ӵ�map��
        codeMap[node->character] = code;
    }
    else {
        // �����������0�������������1
        std::vector<bool> leftCode = code;
        leftCode.push_back(false);
        encodeHelper(node->left, leftCode, codeMap);

        std::vector<bool> rightCode = code;
        rightCode.push_back(true);
        encodeHelper(node->right, rightCode, codeMap);
    }
}

