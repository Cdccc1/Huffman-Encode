#pragma once


#include "frequency_counter.h"
#include "h_priority_queue.h"
#include <bitset>

class HuffmanTree
{
public:

	// 树节点结构Node定义
	struct Node {
		std::string character;// 字符
		int frequency;
		Node* left;
		Node* right;

		// 节点初始化
		Node(std::string ch, int freq, Node* leftChild = nullptr, Node* rightChild = nullptr)
		: character(ch), frequency(freq), left(leftChild), right(rightChild) {}

		// 自定义类型重载比较函数, 字符频率高的节点被视为权重小的节点
		bool operator<(const Node& other) const {
			return frequency > other.frequency;
		}
	};

	struct Cmp
	{
		bool operator()(const Node* left, const Node* right) const
		{
			return left->frequency > right->frequency;
		}
	};
	
	// 构造函数和析构函数
	HuffmanTree();
	~HuffmanTree();

	// 建树
	void buildTree(const std::map<std::string, int>& frequencies);

	// 获取根节点
	Node* getRoot() const;

	// 哈夫曼树编码
	std::map<std::string, std::vector<bool>> encode();


private:

	Node* root;  // 指向哈夫曼树根节点的指针

	// 递归生成编码，Helper
	// void encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap);
	void encodeHelper(Node* node, std::vector<bool> code, std::map<std::string, std::vector<bool>>& codeMap);
	
	
	// 递归释放树内存
	void freeTree(Node* node);
};

