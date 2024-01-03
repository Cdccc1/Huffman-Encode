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

    // 读取压缩文件并进行解压缩，输出到指定文件
    void decompressFile(const std::wstring& inputFilename, const std::wstring& outputFilename);

    // 从compressor那儿获取构建完成的哈夫曼树
    void buildTree(HuffmanTree& tree);

private:
    // 哈夫曼树实例
    HuffmanTree& huffmanTree;

    // 实际进行解压缩的函数
    void decompress(const std::wstring& inputFilename, const std::wstring& outputFilename);
};

