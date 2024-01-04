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
	void compressFile(const std::string& inputFilename, const std::string& outputFilename);

	// 读取文件，进行解压缩，输出到指定文件
	void decompressFile(const std::string& inputFilename, const std::string& outputFilename);

	// 返回创建好的哈夫曼树
	HuffmanTree& getHuffmanTree();
private:

	// 字符频率统计表
	std::map<std::string, int> frequencyTable;

	// 哈夫曼编码表
	std::map<std::string, std::vector<bool>> codes;

	// 哈夫曼树实例
	HuffmanTree huffmanTree;

	// 读取文件并统计字符频率
	void countFrequency(const std::string& inputFilename);

	// 构建哈夫曼树并生成编码
	void buildCodes();

	// 实际进行压缩的函数
	void compress(const std::string& inputFilename, const std::string& outputFilename);

	// 实际解压缩函数
	void decompress(const std::string& inputFilename, const std::string& outputFilename);

	auto GetBoolVectorStartAddress(std::vector<bool>& vec) {
	#ifdef __GNUC__
			/*方法一
			auto begin = vec.begin();
			return begin._M_p;
			*/

			//方法二
			auto Impl = vec._M_get_Bit_allocator(); //获取_Bvector_impl类型的_M_impl;
			return Impl._M_start._M_p; //Impl._M_start就是begin返回的迭代器
	#else
			/*方法一
			auto& source = vec._Myvec;
			return &source[0];*/

			//方法二
			auto begin = vec.begin();
			return begin._Myptr;
	#endif
	}
	

};

