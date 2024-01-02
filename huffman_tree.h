#pragma once
#include "frequency_counter.h"
#include "h_priority_queue.h"


class HuffmanTree
{
public:

	// 树节点结构Node定义
	struct Node {
		wchar_t character;// 字符
		int frequency;
		Node* left;
		Node* right;

		// 节点初始化
		Node(wchar_t ch, int freq, Node* leftChild = nullptr, Node* rightChild = nullptr)
		: character(ch), frequency(freq), left(leftChild), right(rightChild) {}

		// 自定义类型重载比较函数, 字符频率高的节点被视为权重小的节点
		bool operator<(const Node& other) const {
			return frequency > other.frequency;
		}
	};
	
	// 构造函数和析构函数
	HuffmanTree();
	~HuffmanTree();

	// 建树
	void buildTree(const std::map<std::wstring, int>& frequencies);

	// 哈夫曼树编码
	std::map<wchar_t, std::wstring> encode();

	// 解码
	std::wstring decode(const std::wstring& encodedStr);

private:

	Node* root;  // 指向哈夫曼树根节点的指针

	// 递归生成编码，Helper
	void encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap);

	// 递归释放树内存
	void freeTree(Node* node);

};

