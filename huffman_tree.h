#pragma once
#include "frequency_counter.h"
#include "h_priority_queue.h"


class HuffmanTree
{
public:

	// ���ڵ�ṹNode����
	struct Node {
		wchar_t character;// �ַ�
		int frequency;
		Node* left;
		Node* right;

		// �ڵ��ʼ��
		Node(wchar_t ch, int freq, Node* leftChild = nullptr, Node* rightChild = nullptr)
		: character(ch), frequency(freq), left(leftChild), right(rightChild) {}

		// �Զ����������رȽϺ���, �ַ�Ƶ�ʸߵĽڵ㱻��ΪȨ��С�Ľڵ�
		bool operator<(const Node& other) const {
			return frequency > other.frequency;
		}
	};
	
	// ���캯������������
	HuffmanTree();
	~HuffmanTree();

	// ����
	void buildTree(const std::map<std::wstring, int>& frequencies);

	// ������������
	std::map<wchar_t, std::wstring> encode();

	// ����
	std::wstring decode(const std::wstring& encodedStr);

private:

	Node* root;  // ָ������������ڵ��ָ��

	// �ݹ����ɱ��룬Helper
	void encodeHelper(Node* node, std::wstring code, std::map<wchar_t, std::wstring>& codeMap);

	// �ݹ��ͷ����ڴ�
	void freeTree(Node* node);

};

