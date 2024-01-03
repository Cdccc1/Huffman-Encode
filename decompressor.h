#pragma once

#include "huffman_tree.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

class Decompressor
{
public:
    Decompressor() = delete;
    Decompressor(HuffmanTree& huf)
        : huffmanTree(huf) {}
    ~Decompressor();

    // ��ȡѹ���ļ������н�ѹ���������ָ���ļ�
    void decompressFile(const std::wstring& inputFilename, const std::wstring& outputFilename);

    // ��compressor�Ƕ���ȡ������ɵĹ�������
    void buildTree(HuffmanTree& tree);

private:
    // ��������ʵ��
    HuffmanTree& huffmanTree;

    // ʵ�ʽ��н�ѹ���ĺ���
    void decompress(const std::wstring& inputFilename, const std::wstring& outputFilename);
};

