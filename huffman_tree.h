#pragma once


#include "frequency_counter.h"
#include "h_priority_queue.h"
#include <bitset>
#include <queue>

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

		Node(std::string s) : character(s), left(nullptr), right(nullptr) {}
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

	//二进制树
	std::vector<bool> Tree;
	//层次遍历
	void Hierachicalorder();
	//层次遍历建树
	Node* buildingHuffmanTree(const std::vector<bool>& levelOrder)
	{
		if (levelOrder.empty())
		{
			return nullptr;
		}
		std::string s = "0";// 非叶子节点就是0
		Node* rt = new Node(s);// 根节点
		Node* current = rt;// 当前节点用于建树
		int index = 1;// 用于遍历vectorbool里二进制位
		std::queue<Node*> q;// 用于广搜
		q.push(rt);
		int levelOrderSize = levelOrder.size();
		while (index < levelOrderSize)
		{
			// 从队列中取出队首
			Node* node = q.front();
			q.pop();

			// 
			if (index < levelOrder.size())// 如果下标合法
			{
				node->left = new Node(s);
				if (levelOrder[index])// 如果当前二进制序列中的1, 说明遇到叶子结点
				{
					char value = 0; // 存字节
					int length = 0; // 这个字的字节长度
					std::string S;// 构建的字
					
					// 数字节长度
					for (int i = 1; i <= 8; i++)
					{
						length = (length << 1) + levelOrder[index + i];
					}

					index += 8;// 移动指针

					// 读取二进制内容
					for (int i = 0; i < length; i++)
					{
						value = 0;
						for (int j = 1; j <= 8; j++)
						{
							value = (value << 1) + levelOrder[index + j];
						}
						index = index + 8;
						S.push_back(value);
					}
					
					node->left->character = S;
					index++;
				}
				else
				{
					q.push(node->left);
					index += 1;
				}
			}


			if (index < levelOrder.size())
			{
				node->right = new Node(s);
				
				if (levelOrder[index])
				{
					char value = 0;
					int length = 0;
					std::string S;
					for (int i = 1; i <= 8; i++)
					{
						length = (length << 1) + levelOrder[index + i];
					}

					index += 8;

					for (int i = 0; i < length; i++)
					{
						value = 0;
						for (int j = 1; j <= 8; j++)
						{
							value = (value << 1) + levelOrder[index + j];
						}
						S.push_back(value);
						index = index + 8;
					}

					node->right->character = S;
					index++;
				}
				else
				{
					q.push(node->right);
					index += 1;
				}
			}
		}
		root = rt;
		return rt;
	}
private:

	Node* root;  // 指向哈夫曼树根节点的指针
	
	// 递归生成编码，Helper
	// void encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap);
	void encodeHelper(Node* node, std::vector<bool> code, std::map<std::string, std::vector<bool>>& codeMap);
	
	
	// 递归释放树内存
	void freeTree(Node* node);
};

