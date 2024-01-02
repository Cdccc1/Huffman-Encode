#pragma once

#include "huffman_tree.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

class Decompressor
{
public:
    Decompressor();
    ~Decompressor();

    // ��ȡѹ���ļ������н�ѹ���������ָ���ļ�
    void decompressFile(const std::wstring& inputFilename, const std::wstring& outputFilename);

private:
    // �洢�ַ�Ƶ��ͳ�ƽ������Ҫ��ѹ���ļ���ȡ
    std::map<std::wstring, int> frequencies;

    // ��������ʵ��
    HuffmanTree huffmanTree;

    // ��ѹ���ļ���ȡ�ַ�Ƶ��ͳ����Ϣ
    void readFrequency(const std::wstring& inputFilename);

    // ������������
    void buildTree();

    // ʵ�ʽ��н�ѹ���ĺ���
    void decompress(const std::wstring& inputFilename, const std::wstring& outputFilename);
};

