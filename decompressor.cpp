#include "decompressor.h"


Decompressor::~Decompressor() {}

// ʵ�ʽ���ѹ���ĺ���
void Decompressor::decompress(const std::wstring& inputFilename, const std::wstring& outputFilename)
{
	// �Զ����Ʒ�ʽ�������ļ�
	std::wifstream inputFile(inputFilename, std::ios::binary);
	std::wofstream outputFile(outputFilename);
	// ����޷������������ļ����׳���`��
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
	//ȥ����䲿��

	std::wstring currentcode;
	//currentcode = huffmanTree.decode(binaryStream);
	for (int i = 0; i < currentcode.size(); i++)
	{
		outputFile.put(currentcode[i]);
	}
	
	// �ر��ļ�
	inputFile.close();
	outputFile.close();
}

// ��ȡѹ���ļ������н�ѹ���������ָ���ļ�
void Decompressor::decompressFile(const std::wstring& inputFilename, const std::wstring& outputFilename)
{
	decompress(inputFilename, outputFilename);
}

void Decompressor::buildTree(HuffmanTree& tree)
{
	huffmanTree = tree;
}