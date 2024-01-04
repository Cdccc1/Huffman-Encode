#pragma once


#include "frequency_counter.h"
#include "h_priority_queue.h"
#include <bitset>
#include <queue>

class HuffmanTree
{
public:

	// ���ڵ�ṹNode����
	struct Node {
		std::string character;// �ַ�
		int frequency;
		Node* left;
		Node* right;

		// �ڵ��ʼ��
		Node(std::string ch, int freq, Node* leftChild = nullptr, Node* rightChild = nullptr)
		: character(ch), frequency(freq), left(leftChild), right(rightChild) {}

		Node(std::string s) : character(s), left(nullptr), right(nullptr) {}
		// �Զ����������رȽϺ���, �ַ�Ƶ�ʸߵĽڵ㱻��ΪȨ��С�Ľڵ�
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
	
	// ���캯������������
	HuffmanTree();
	~HuffmanTree();

	// ����
	void buildTree(const std::map<std::string, int>& frequencies);

	// ��ȡ���ڵ�
	Node* getRoot() const;

	// ������������
	std::map<std::string, std::vector<bool>> encode();

	//��������
	std::vector<bool> Tree;
	//��α���
	void Hierachicalorder();
	//��α�������
	Node* buildingHuffmanTree(const std::vector<bool>& levelOrder)
	{
		if (levelOrder.empty())
		{
			return nullptr;
		}
		std::string s = "0";// ��Ҷ�ӽڵ����0
		Node* rt = new Node(s);// ���ڵ�
		Node* current = rt;// ��ǰ�ڵ����ڽ���
		int index = 1;// ���ڱ���vectorbool�������λ
		std::queue<Node*> q;// ���ڹ���
		q.push(rt);
		int levelOrderSize = levelOrder.size();
		while (index < levelOrderSize)
		{
			// �Ӷ�����ȡ������
			Node* node = q.front();
			q.pop();

			// 
			if (index < levelOrder.size())// ����±�Ϸ�
			{
				node->left = new Node(s);
				if (levelOrder[index])// �����ǰ�����������е�1, ˵������Ҷ�ӽ��
				{
					char value = 0; // ���ֽ�
					int length = 0; // ����ֵ��ֽڳ���
					std::string S;// ��������
					
					// ���ֽڳ���
					for (int i = 1; i <= 8; i++)
					{
						length = (length << 1) + levelOrder[index + i];
					}

					index += 8;// �ƶ�ָ��

					// ��ȡ����������
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

	Node* root;  // ָ������������ڵ��ָ��
	
	// �ݹ����ɱ��룬Helper
	// void encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap);
	void encodeHelper(Node* node, std::vector<bool> code, std::map<std::string, std::vector<bool>>& codeMap);
	
	
	// �ݹ��ͷ����ڴ�
	void freeTree(Node* node);
};

