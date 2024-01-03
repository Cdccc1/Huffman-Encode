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
	// 构造和析构函数
	Compressor();
	~Compressor();

	// 读取文件，进行压缩，输出到指定文件
	void compressFile(const std::wstring& inputFilename, const std::wstring& outputFilename);

	// 返回创建好的哈夫曼树
	HuffmanTree& getHuffmanTree();
private:
	// 字符频率统计表
	std::map<std::wstring, int> frequencyTable;

	// 哈夫曼编码表
	std::map<wchar_t, std::wstring> codes;

	// 哈夫曼树实例
	HuffmanTree huffmanTree;

	// 读取文件并统计字符频率
	void countFrequency(const std::wstring& inputFilename);

	// 构建哈夫曼树并生成编码
	void buildCodes();

	// 实际进行压缩的函数
	void compress(const std::wstring& inputFilename, const std::wstring& outputFilename);
};

