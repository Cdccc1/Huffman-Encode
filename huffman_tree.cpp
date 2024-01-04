#include "huffman_tree.h"

// 显式实例化
template class PriorityQueue<HuffmanTree::Node*, HuffmanTree::Cmp>;


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

// 返回根节点指针
HuffmanTree::Node* HuffmanTree::getRoot() const {
    return root; 
}

// 哈夫曼树编码
std::map<std::string, std::vector<bool>> HuffmanTree::encode() {
    std::map<std::string, std::vector<bool>> codeMap;
    encodeHelper(root, std::vector<bool>(), codeMap);

    // 遍历codeMap并打印字符及其对应的编码
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


// 递归编码Helper
// 修改参数类型为 std::vector<bool>，以适应动态长度的编码
void HuffmanTree::encodeHelper(Node* node, std::vector<bool> code, std::map<std::string, std::vector<bool>>& codeMap) {
    if (!node) return;
    if (!node->left && !node->right) {
        // 当到达叶子节点时，将编码添加到map中
        codeMap[node->character] = code;
    }
    else {
        // 向左子树添加0，向右子树添加1
        std::vector<bool> leftCode = code;
        leftCode.push_back(false);
        encodeHelper(node->left, leftCode, codeMap);

        std::vector<bool> rightCode = code;
        rightCode.push_back(true);
        encodeHelper(node->right, rightCode, codeMap);
    }
}

