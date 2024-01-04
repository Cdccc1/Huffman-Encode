#include "decompressor.h"


Decompressor::~Decompressor() {}

// 实际进行压缩的函数
void Decompressor::decompress(const std::wstring& inputFilename, const std::wstring& outputFilename)
{
	// 以二进制方式打开输入文件
	std::wifstream inputFile(inputFilename, std::ios::binary);
	std::wofstream outputFile(outputFilename);
	// 如果无法打开输入或输出文件，抛出异`常
	if (!inputFile.is_open() || !outputFile.is_open()) {
		std::wcerr << "Error opening files!" << std::endl;
		throw std::runtime_error("Cannot open input/output files.");
	}
	
	char padding_byte;
	inputFile.read(reinterpret_cast<wchar_t*>(&padding_byte), 8);
	int padding{ padding_byte };
	
	// std::wstring binaryStream;
	// wchar_t byte;
	// std::vector<char> binaryStream;
	std::wstring binaryStream;
	wchar_t byte;
	while (inputFile.read(&byte, sizeof(byte))) {
		binaryStream.push_back(byte);
	}
	/*
	while (inputFile>>byte)
	{
		binaryStream.push_back(byte);
	}
	*/
	//去除填充部分

	std::wstring currentcode;
	//currentcode = huffmanTree.decode(binaryStream);
	for (int i = 0; i < currentcode.size(); i++)
	{
		outputFile.put(currentcode[i]);
	}
	
	// 关闭文件
	inputFile.close();
	outputFile.close();
}

// 读取压缩文件并进行解压缩，输出到指定文件
void Decompressor::decompressFile(const std::wstring& inputFilename, const std::wstring& outputFilename)
{
	decompress(inputFilename, outputFilename);
}

void Decompressor::buildTree(HuffmanTree& tree)
{
	huffmanTree = tree;
}