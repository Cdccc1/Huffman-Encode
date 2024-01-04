#pragma once


#include "frequency_counter.h"
#include "h_priority_queue.h"
#include <bitset>

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


private:

	Node* root;  // ָ������������ڵ��ָ��

	// �ݹ����ɱ��룬Helper
	// void encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap);
	void encodeHelper(Node* node, std::vector<bool> code, std::map<std::string, std::vector<bool>>& codeMap);
	
	
	// �ݹ��ͷ����ڴ�
	void freeTree(Node* node);
};

