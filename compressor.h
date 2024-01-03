#pragma once
#include "frequency_counter.h"
#include "huffman_tree.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <bitset>

class Compressor
{
public:
	// �������������
	Compressor();
	~Compressor();

	// ��ȡ�ļ�������ѹ���������ָ���ļ�
	void compressFile(const std::wstring& inputFilename, const std::wstring& outputFilename);

	// ���ش����õĹ�������
	HuffmanTree& getHuffmanTree();
private:
	// �ַ�Ƶ��ͳ�Ʊ�
	std::map<std::wstring, int> frequencyTable;

	// �����������
	std::map<wchar_t, std::wstring> codes;

	// ��������ʵ��
	HuffmanTree huffmanTree;

	// ��ȡ�ļ���ͳ���ַ�Ƶ��
	void countFrequency(const std::wstring& inputFilename);

	// �����������������ɱ���
	void buildCodes();

	// ʵ�ʽ���ѹ���ĺ���
	void compress(const std::wstring& inputFilename, const std::wstring& outputFilename);
};

