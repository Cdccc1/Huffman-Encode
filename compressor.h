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
	void compressFile(const std::string& inputFilename, const std::string& outputFilename);

	// ��ȡ�ļ������н�ѹ���������ָ���ļ�
	void decompressFile(const std::string& inputFilename, const std::string& outputFilename);

	// ���ش����õĹ�������
	HuffmanTree& getHuffmanTree();
private:

	// �ַ�Ƶ��ͳ�Ʊ�
	std::map<std::string, int> frequencyTable;

	// �����������
	std::map<std::string, std::vector<bool>> codes;

	// ��������ʵ��
	HuffmanTree huffmanTree;

	// ��ȡ�ļ���ͳ���ַ�Ƶ��
	void countFrequency(const std::string& inputFilename);

	// �����������������ɱ���
	void buildCodes();

	// ʵ�ʽ���ѹ���ĺ���
	void compress(const std::string& inputFilename, const std::string& outputFilename);

	// ʵ�ʽ�ѹ������
	void decompress(const std::string& inputFilename, const std::string& outputFilename);

	auto GetBoolVectorStartAddress(std::vector<bool>& vec) {
	#ifdef __GNUC__
			/*����һ
			auto begin = vec.begin();
			return begin._M_p;
			*/

			//������
			auto Impl = vec._M_get_Bit_allocator(); //��ȡ_Bvector_impl���͵�_M_impl;
			return Impl._M_start._M_p; //Impl._M_start����begin���صĵ�����
	#else
			/*����һ
			auto& source = vec._Myvec;
			return &source[0];*/

			//������
			auto begin = vec.begin();
			return begin._Myptr;
	#endif
	}
	

};

