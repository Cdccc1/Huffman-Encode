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

    // 读取压缩文件并进行解压缩，输出到指定文件
    void decompressFile(const std::wstring& inputFilename, const std::wstring& outputFilename);

private:
    // 存储字符频率统计结果，需要从压缩文件读取
    std::map<std::wstring, int> frequencies;

    // 哈夫曼树实例
    HuffmanTree huffmanTree;

    // 从压缩文件读取字符频率统计信息
    void readFrequency(const std::wstring& inputFilename);

    // 构建哈夫曼树
    void buildTree();

    // 实际进行解压缩的函数
    void decompress(const std::wstring& inputFilename, const std::wstring& outputFilename);
};

